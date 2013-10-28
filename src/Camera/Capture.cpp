#include "Camera/Capture.h"

namespace Camera
{
	Capture::Capture(bool p_runInOwnThread, irr::core::dimension2du p_resolution, irr::video::ITexture* p_texture)
	{
		m_texture = p_texture;
		m_resolution = p_resolution;
		m_runInOwnThread = p_runInOwnThread;
		m_params = new CalibrationParams("resources/camera_calibration_out.xml");
		m_capture = cv::VideoCapture(CV_CAP_ANY);
		m_fov = 60.0f;
		m_running = false;

		m_chosen = false;
		m_lost = true;
		// Get the screen size from opencv
		m_size = cv::Size(
			static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_WIDTH)),
			static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_HEIGHT)));
		// Calculate the half of the with and height
		m_sizeHalfed = cv::Size(
			((m_size.width - 1) / 2),
			((m_size.height - 1) / 2));
		m_center = cv::Point(((m_size.width - 1) / 2), ((m_size.height - 1) / 2));
		m_ratio = 0.0f;
		m_pixelDistance = 100.0f;
		m_boundingBox = cv::Rect(0, 0, m_size.width, m_size.height);

		m_corners = Corners();
		m_defaultRotation = 0.0f;

		m_image = cv::Mat(m_size.width, m_size.height, CV_8U);
		// Setup default setings if the calibration info cannot be loaded
		if (!m_params->GetIsOpenedAndGood())
		{
			double fx;
			double fy;
			fx = fy = (m_sizeHalfed.width / std::tan((m_fov / 2) * (irr::core::PI / 180)));
			m_params->SetCameraMatrix((cv::Mat_<double>(3, 3) <<
					fx, 0.0, m_sizeHalfed.width,
					0.0, fy, m_sizeHalfed.height,
					0.0, 0.0, 1.0));
		}
	}

	Capture::~Capture()
	{
		Cleanup();
	}

	void Capture::Cleanup()
	{
		m_running = false;
		if (m_runInOwnThread)
		{
			m_thread->join();
			delete m_thread;
			delete m_mutex;
		}

		cv::destroyAllWindows();
		m_image.release();
		m_capture.release();
		delete m_params;
	}

	void Capture::Start()
	{
		if (m_runInOwnThread)
		{
			if (!m_running)
			{
				m_running = true;
				m_thread = new std::thread(&Capture::Worker, this);
				m_mutex = new std::mutex();
			}
		}
		else
		{
			Work();
		}
	}

	void Capture::Lock()
	{
		if (m_runInOwnThread)
		{
			m_mutex->lock();
		}
	}

	void Capture::Unlock()
	{
		if (m_runInOwnThread)
		{
			m_mutex->unlock();
		}
	}

	void Capture::Work()
	{
		bool lost = true;
		if (m_capture.isOpened())
		{
			CaptureAndUndistort();
			if (!m_image.empty())
			{
				cv::Mat surface = cv::Mat(m_image.clone());
				cv::cvtColor(surface, surface, CV_BGR2HSV);

				if (!m_chosen)
				{
					int index = static_cast<int>(((m_center.y * surface.channels()) * m_size.width) + (m_center.x * surface.channels()));
					// Make sure we can't go out of bounds of the pixel data
					if ((index + 2) <= (sizeof(unsigned char) * (surface.cols * surface.rows * surface.channels())))
					{
						m_color = cv::Scalar(surface.data[(index + 0)], surface.data[(index + 1)], surface.data[(index + 2)]);
					}

					// DEBUG CIRCLE
					cv::circle(m_image, m_center, 5, cv::Scalar(255, 255, 255));
					// DEBUG BOUNDINGBOX
					cv::rectangle(m_image, m_boundingBox, cv::Scalar(255, 255, 255));
				}

				// -----
				// Color detection
				// -----

				int offset = 30;
				cv::Scalar lowerColor = cv::Scalar(m_color.val[0] - offset, m_color.val[1] - (offset * 3), m_color.val[2] - (offset * 3));
				cv::Scalar upperColor = cv::Scalar(m_color.val[0] + offset, m_color.val[1] + (offset * 3), m_color.val[2] + (offset * 3));
				cv::inRange(surface, lowerColor, upperColor, surface);

				cv::medianBlur(surface, surface, 9);
				cv::Canny(surface, surface, 0, 255);

				// -----
				// Find contours
				// -----

				std::vector<std::vector<cv::Point>> contours;
				cv::findContours(surface.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

				for (unsigned int i = 0; i < contours.size(); ++i)
				{
					cv::Mat curve = cv::Mat(contours[i]);
					Corners approx;
					// Convert from std::vector<cv::Point> to Corners
					curve.convertTo(curve, cv::Mat(approx).type());

					cv::approxPolyDP(curve, approx, (cv::arcLength(curve, true) * 0.02), true);
					if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
					{
						continue;
					}

					int offset = 30;
					cv::Rect boundingBox = cv::boundingRect(approx);
					boundingBox.x -= offset;
					boundingBox.y -= offset;
					boundingBox.width += (offset * 2);
					boundingBox.height += (offset * 2);

					if (approx.size() == 4 && boundingBox.contains(m_center))
					{
						m_boundingBox = boundingBox;

						cv::Point2f center;
						if (m_chosen)
						{
							center = cv::Point2f(0, 0);
							for (unsigned int i = 0; i < approx.size(); ++i)
							{
								center += approx[i];
							}
							center *= (1.0 / approx.size());
						}
						else
						{
							center = m_center;
						}

						if (SortCorners(approx, center))
						{
							// -----
							// At this point we are sure that we have a correct set of corners to work with
							// -----

							Lock();
							lost = false;
							m_center = center;
							m_corners.clear();
							m_corners = approx;
							CalculateShortestAndLongestLine(m_corners);
	
							irr::core::line2df top = irr::core::line2df(
									irr::core::vector2df(m_corners.at(0).x, m_corners.at(0).y),
									irr::core::vector2df(m_corners.at(1).x, m_corners.at(1).y));
							irr::core::line2df left = irr::core::line2df(
									irr::core::vector2df(m_corners.at(1).x, m_corners.at(1).y),
									irr::core::vector2df(m_corners.at(2).x, m_corners.at(2).y));

							m_lineRatio = left.getLength() / top.getLength();

							Unlock();
						}
					}

					// Release the curve
					curve.release();
				}

				if (m_chosen && lost)
				{
					// ERROR BOUNDINGBOX
					cv::rectangle(m_image, m_boundingBox, cv::Scalar(0, 0, 255));
				}

				m_lost = lost;
				//cv::imshow("surface", surface);
				//cv::waitKey(1);
				surface.release();

				// Update the irrlicht texture with the camera frame
				CopyToTexture();
			}
		}
	}

	void Capture::Worker()
	{
		while (m_running)
		{
			Work();
		}
	}

	void Capture::FindStartAndEndPoints(cv::Mat p_frame, irr::core::vector3df* p_startPoints, irr::core::vector3df* p_endPoints)
	{
		if (m_corners.size() == 4 && m_chosen)
		{
			PointDetector pd;

			pd.FindPointsInFrame(p_frame, m_corners, p_startPoints, p_endPoints);
		}
	}

	bool Capture::OnEvent(const irr::SEvent& P_EVT)
	{
		if (P_EVT.EventType == irr::EEVENT_TYPE::EET_MOUSE_INPUT_EVENT)
		{
			//devide by zero?
			m_center.x = static_cast<float>((P_EVT.MouseInput.X - 1) / (m_resolution.Width / m_size.width));
			m_center.y = static_cast<float>((P_EVT.MouseInput.Y - 1) / (m_resolution.Height / m_size.height));

			if (P_EVT.MouseInput.isLeftPressed())
			{
				m_chosen = true;
			}
		}

		return false;
	}

	irr::core::matrix4 Capture::GetTransformMatrix(irr::core::matrix4 p_cameraProjection)
	{
		// Create a new matrix to use for transformation
		irr::core::matrix4 transformation = irr::core::IdentityMatrix;

		// Only do calculations when we have 4 corners
		if (m_corners.size() == 4)
		{
			irr::core::matrix4 scaling = irr::core::IdentityMatrix;
			irr::core::matrix4 rotation = irr::core::IdentityMatrix;
			irr::core::matrix4 translation = irr::core::IdentityMatrix;

			Lock();
			// Invert the camera projection matrix
			p_cameraProjection.makeInverse();

			// Caltulate the center x and y from the top left corner
			float ltCenterX = (m_center.x - m_sizeHalfed.width);
			float ltCenterY = (m_center.y - m_sizeHalfed.height);

			// Calculates the ratio betwee the longest game line and longest capture line
			m_ratio = m_longestGameLine.getLength() / m_longestLine.getLength();
			// Multiplies the game line length with the ratio to get the pixel distance
			m_pixelDistance = m_longestGameLine.getLength() * m_ratio;

			// -----
			// Set the scaling
			// -----

			// Apply the scaling (no scaling; default to 1.0f)
			scaling.setScale(irr::core::vector3df(1.0f, 1.0f, 1.0f));

			// -----
			// Set the rotation
			// -----

			irr::core::line2df top = irr::core::line2df(
					irr::core::vector2df(m_corners.at(0).x, m_corners.at(0).y),
					irr::core::vector2df(m_corners.at(1).x, m_corners.at(1).y));

			irr::core::line2df bottom = irr::core::line2df(
					irr::core::vector2df(m_corners.at(2).x, m_corners.at(2).y),
					irr::core::vector2df(m_corners.at(3).x, m_corners.at(3).y));

			irr::core::line2df right = irr::core::line2df(
					irr::core::vector2df(m_corners.at(1).x, m_corners.at(1).y),
					irr::core::vector2df(m_corners.at(2).x, m_corners.at(2).y));

			irr::core::line2df left = irr::core::line2df(
					irr::core::vector2df(m_corners.at(3).x, m_corners.at(3).y),
					irr::core::vector2df(m_corners.at(0).x, m_corners.at(0).y));

			float range = 0.2f;
			// Create a 3D vector to contain the new angles
			irr::core::vector3df angles = irr::core::vector3df(
					 static_cast<float>(((top.getLength() / bottom.getLength()) - 1.0f) * (irr::core::HALF_PI / range)),
					-static_cast<float>(std::atan2(top.end.Y - top.start.Y, top.end.X - top.start.X) * (180.0f / irr::core::PI)),
					 static_cast<float>(((right.getLength() / left.getLength()) - 1.0f) * (irr::core::HALF_PI / range)));

			rotation.setRotationRadians(irr::core::vector3df(
					-static_cast<float>(angles.Z > irr::core::HALF_PI ? irr::core::HALF_PI : (angles.Z < -irr::core::HALF_PI ? -irr::core::HALF_PI : angles.Z)),
					 static_cast<float>(m_defaultRotation + (angles.Y * (irr::core::PI / 180.0f))),
					-static_cast<float>(angles.X > irr::core::HALF_PI ? irr::core::HALF_PI : (angles.X < -irr::core::HALF_PI ? -irr::core::HALF_PI : angles.X))));

			// -----
			// Set the translation
			// -----

			// Create a 3D vector to contain the new position
			irr::core::vector3df position = irr::core::vector3df(
					static_cast<float>(ltCenterX),
					static_cast<float>(ltCenterY),
					static_cast<float>(0.0f));
			// Transform using the inverted camera matrix
			p_cameraProjection.transformVect(position);

			// Apply transformation (y transformation is done in the camera)
			translation.setTranslation(irr::core::vector3df(
					 static_cast<float>(position.Y * (m_pixelDistance / m_sizeHalfed.height)),
					-static_cast<float>(position.Z),
					 static_cast<float>(position.X * (m_pixelDistance / m_sizeHalfed.width))));	

			// Merge scaling, rotation and translation into the transformation
			transformation = scaling * rotation * translation;
			// Make it inverted
			transformation.makeInverse();

			Unlock();
		}

		return transformation;
	}

	bool Capture::HasChosen()
	{
		return m_chosen;
	}

	bool Capture::IsLost()
	{
		return m_lost;
	}

	float Capture::GetFov()
	{
		return m_fov;
	}

	void Capture::SetFov(float p_fov)
	{
		m_fov = p_fov;
	}

	float Capture::GetPixelDistance()
	{
		return m_pixelDistance;
	}

	irr::core::line2df Capture::GetLongestGameLine()
	{
		return m_longestGameLine;
	}

	void Capture::SetLongestGameLine(irr::core::line2df p_longestGameLine)
	{
		m_longestGameLine = p_longestGameLine;
	}

	irr::core::line2df Capture::GetCalculatedShortestGameLine()
	{
		irr::core::line2df line = irr::core::line2df(
				irr::core::vector2df(0.0f, 0.0f),
				irr::core::vector2df(0.0f, (m_longestGameLine.getLength() * m_lineRatio)));

		return line;
	}

	void Capture::CaptureAndUndistort()
	{
		m_capture >> m_image;
		if (m_params->GetIsOpenedAndGood() && !m_image.empty())
		{
			cv::undistort(m_image.clone(), m_image,
					m_params->GetCameraMatrix(),
					m_params->GetDistortionCoefficients());
		}
	}

	void Capture::CopyToTexture()
	{
		cv::cvtColor(m_image, m_image, CV_BGR2BGRA, 4);
		unsigned char* buffer = static_cast<unsigned char*>(m_texture->lock());
		memcpy(buffer, m_image.data, (sizeof(unsigned char) * ((m_image.rows * m_image.cols) * m_image.channels())));
		m_texture->unlock();
	}

	cv::Point2f Capture::ComputeCross(cv::Vec4i p_vec1, cv::Vec4i p_vec2)
	{
		int x1 = p_vec1[0];
		int y1 = p_vec1[1];

		int x2 = p_vec1[2];
		int y2 = p_vec1[3];

		int x3 = p_vec2[0];
		int y3 = p_vec2[1];

		int x4 = p_vec2[2];
		int y4 = p_vec2[3];

		if (float d = ((float) (x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)))
		{
			cv::Point2f pt;
			pt.x = ((x1*y2 - y1*x2) * (x3 - x4) - (x1 - x2) * (x3*y4 - y3*x4)) / d;
			pt.y = ((x1*y2 - y1*x2) * (y3 - y4) - (y1 - y2) * (x3*y4 - y3*x4)) / d;
			return pt;
		}
		else
		{
			return cv::Point2f(-1, -1);
		}
	}

	bool Capture::SortCorners(Corners& p_corners, cv::Point2f p_center)
	{
		Corners top;
		Corners bot;
		for (unsigned int i = 0; i < p_corners.size(); i++)
		{
			if (p_corners[i].y < p_center.y)
			{
				top.push_back(p_corners[i]);
			}
			else
			{
				bot.push_back(p_corners[i]);
			}
		}

		if (top.size() != bot.size())
		{
			return false;
		}

		Corners corners;
		corners.push_back(top[0].x > top[1].x ? top[1] : top[0]);
		corners.push_back(top[0].x > top[1].x ? top[0] : top[1]);
		corners.push_back(bot[0].x < bot[1].x ? bot[1] : bot[0]);
		corners.push_back(bot[0].x < bot[1].x ? bot[0] : bot[1]);

		if (m_topLeft.x > 0 && m_topLeft.y > 0 && m_chosen)
		{
			int offset = 30;
			cv::Rect tlbb = cv::Rect(
					static_cast<int>(m_topLeft.x - offset),
					static_cast<int>(m_topLeft.y - offset),
					offset * 2,
					offset * 2);

			for (unsigned int i = 0; i < corners.size(); ++i)
			{
				corners.push_back(corners.front());
				corners.erase(corners.begin());

				if (tlbb.contains(corners.at(0)))
				{
					break;
				}
			}
		}

		// Update m_topLeft
		m_topLeft = corners.at(0);

		p_corners.clear();
		p_corners.push_back(corners.at(0));
		p_corners.push_back(corners.at(1));
		p_corners.push_back(corners.at(2));
		p_corners.push_back(corners.at(3));
		return true;
	}

	void Capture::CalculateShortestAndLongestLine(Corners p_corners)
	{
		irr::core::line2df shortestLine;
		irr::core::line2df longestLine;

		for (unsigned int i = 0; i < p_corners.size(); ++i)
		{
			//Alex wat doet het vraagteken en enzo. ziet er apart uit.
			unsigned int j = (i >= (p_corners.size() - 1))
					? 0
					: (i + 1);

			unsigned int k = (j >= (p_corners.size() - 1))
					? 0
					: (j + 1);

			irr::core::line2df tmpLine = irr::core::line2df(
					irr::core::vector2df(p_corners[i].x, p_corners[i].y),
					irr::core::vector2df(p_corners[j].x, p_corners[j].y));

			//if (tmpLine.getLength() > longestLine.getLength())
			//{
			//	longestLine = tmpLine;
			//}

			if (tmpLine.getLength() < shortestLine.getLength() || shortestLine.getLength() <= 2.0f)
			{
				shortestLine = tmpLine;
				longestLine = irr::core::line2df(
						irr::core::vector2df(p_corners[j].x, p_corners[j].y),
						irr::core::vector2df(p_corners[k].x, p_corners[k].y));
			}
		}

		m_shortestLine = shortestLine;
		m_longestLine = longestLine;
		m_ratio = m_shortestLine.getLength() / m_longestLine.getLength();
	}

	cv::Mat Capture::GetImage()
	{
		return m_image;
	}

	irr::core::dimension2du Capture::GetCaptureSize()
	{
		return irr::core::dimension2du(m_size.width, m_size.height);
	}
}