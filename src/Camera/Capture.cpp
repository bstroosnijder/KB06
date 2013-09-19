#include "Camera/Capture.h"

namespace Camera
{
	Capture::Capture(irr::video::ITexture* p_texture)
	{
		m_texture = p_texture;
		m_params = new CalibrationParams("resources/camera_calibration_out.xml");
		m_capture = cv::VideoCapture(CV_CAP_ANY);

		m_chosen = false;
		m_lost = true;
		m_size = cv::Size(
				static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_WIDTH)),
				static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_HEIGHT)));
		m_center = cv::Point(((m_size.width - 1) / 2), ((m_size.height - 1) / 2));
		m_boundingBox = cv::Rect(0, 0, m_size.width, m_size.height);
		m_corners = Corners();

		m_image = cv::Mat(m_size.width, m_size.height, CV_8U);
	}

	Capture::~Capture()
	{
		Cleanup();
	}

	void Capture::Cleanup()
	{
		cv::destroyAllWindows();
		m_image.release();
		m_capture.release();
		delete m_params;
	}

	void Capture::Update()
	{
		m_lost = true;
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
					m_color = cv::Scalar(surface.data[(index + 0)], surface.data[(index + 1)], surface.data[(index + 2)]);

					// DEBUG CIRCLE
					cv::circle(m_image, m_center, 5, cv::Scalar(255, 255, 255));
					// DEBUG BOUNDINGBOX
					cv::rectangle(m_image, m_boundingBox, cv::Scalar(255, 255, 255));
				}

				int offset = 30;
				cv::Scalar lowerColor = cv::Scalar(m_color.val[0] - offset, m_color.val[1] - (offset * 3), m_color.val[2] - (offset * 3));
				cv::Scalar upperColor = cv::Scalar(m_color.val[0] + offset, m_color.val[1] + (offset * 3), m_color.val[2] + (offset * 3));
				cv::inRange(surface, lowerColor, upperColor, surface);

				cv::medianBlur(surface, surface, 9);
				cv::Canny(surface, surface, 0, 255);



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
							m_lost = false;
							m_center = center;
							m_corners = approx;
						}
					}

					// Release the curve
					curve.release();
				}

				if (m_corners.size() == 4 && m_chosen)
				{
					// Define the destination image
					cv::Mat quad = cv::Mat::zeros(300, 300, CV_8U);

					// Corners of the destination image
					Corners quad_pts;
					quad_pts.push_back(cv::Point2f(0, 0));
					quad_pts.push_back(cv::Point2f(quad.cols, 0));
					quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
					quad_pts.push_back(cv::Point2f(0, quad.rows));

					// Get transformation matrix
					m_matrix = cv::getPerspectiveTransform(m_corners, quad_pts);


					// Apply perspective transformation
					cv::warpPerspective(m_image, quad, m_matrix, quad.size());
					cv::imshow("quadrilateral", quad);
				}






				if (m_chosen && m_lost)
				{
					// ERROR BOUNDINGBOX
					cv::rectangle(m_image, m_boundingBox, cv::Scalar(0, 0, 255));
				}

				//cv::imshow("surface", surface);
				surface.release();

				// Update the irrlicht texture with the camera frame
				CopyToTexture();
			}
		}
	}

	bool Capture::OnEvent(const irr::SEvent& P_EVT)
	{
		if (P_EVT.EventType == irr::EEVENT_TYPE::EET_MOUSE_INPUT_EVENT)
		{
			m_center.x = static_cast<float>(P_EVT.MouseInput.X);
			m_center.y = static_cast<float>(P_EVT.MouseInput.Y);

			if (P_EVT.MouseInput.isLeftPressed())
			{
				m_chosen = true;
			}
		}

		return false;
	}

	irr::core::matrix4 Capture::GetProjectionMatrix()
	{
		irr::core::matrix4 projection = irr::core::IdentityMatrix;

		// Decompose the projection matrix into:
		cv::Mat K(3, 3, cv::DataType<float>::type); // intrinsic parameter matrix
		cv::Mat R(3, 3, cv::DataType<float>::type); // rotation matrix
		cv::Mat T(4, 1, cv::DataType<float>::type); // translation vector

		cv::decomposeProjectionMatrix(m_matrix, K, R, T);
		std::cout << "K: " << K << std::endl;
		std::cout << "R: " << R << std::endl;
		std::cout << "T: " << T << std::endl;

		return projection;
	}

	bool Capture::HasChosen()
	{
		return m_chosen;
	}

	bool Capture::IsLost()
	{
		return m_lost;
	}

	void Capture::CaptureAndUndistort()
	{
		m_capture >> m_image;
		//cv::undistort(m_image, m_image,
		//	m_params->GetCameraMatrix(),
		//	m_params->GetDistortionCoefficients());
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

	bool Capture::SortCorners(Corners p_corners, cv::Point2f p_center)
	{
		std::vector<cv::Point2f> top;
		std::vector<cv::Point2f> bot;
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

		cv::Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
		cv::Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
		cv::Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
		cv::Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];

		p_corners.clear();
		p_corners.push_back(tl);
		p_corners.push_back(tr);
		p_corners.push_back(br);
		p_corners.push_back(bl);

		return true;
	}
}