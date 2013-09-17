#include "Camera/Capture.h"

namespace Camera
{
	Capture::Capture(irr::video::ITexture* p_texture)
	{
		m_texture = p_texture;
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

		cv::namedWindow("SLIDERS");
		cv::createTrackbar("OFFSET", "SLIDERS", &m_value, 60);
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
	}

	void Capture::Update()
	{
		m_lost = true;
		if (m_capture.isOpened())
		{
			m_capture >> m_image;
			if (!m_image.empty())
			{
				cv::Mat surface = cv::Mat(m_image.clone());
				cv::cvtColor(surface, surface, CV_BGR2HSV);

				if (!m_chosen)
				{
					int index = (((m_center.y * surface.channels()) * m_size.width) + (m_center.x * surface.channels()));
					m_color = cv::Scalar(surface.data[(index + 0)], surface.data[(index + 1)], surface.data[(index + 2)]);

					// DEBUG CIRCLE
					cv::circle(m_image, m_center, 5, cv::Scalar(255, 255, 255));
				}

				//cv::Mat test = surface.clone();
				//cv::bilateralFilter(test, surface, 9, 150.0, 150.0);

				int offset = m_value;
				cv::Scalar lowerColor = cv::Scalar(m_color.val[0] - offset, m_color.val[1] - (offset * 3), m_color.val[2] - (offset * 3));
				cv::Scalar upperColor = cv::Scalar(m_color.val[0] + offset, m_color.val[1] + (offset * 3), m_color.val[2] + (offset * 3));
				cv::inRange(surface, lowerColor, upperColor, surface);

				//int stuff = 1;
				//cv::dilate(surface, surface, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(((2 * stuff) + 1), ((2 * stuff) + 1))));
				//cv::erode(surface, surface, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(((2 * stuff) + 1), ((2 * stuff) + 1))));
				cv::medianBlur(surface, surface, 9);
				cv::Canny(surface, surface, 0, 255);
				cv::imshow("surface", surface);






				std::vector<cv::Vec4i> lines;
				cv::HoughLinesP(surface, lines, 1.0, (CV_PI / 180), 20, 0, 50);

				for (unsigned int i = 0; i < lines.size(); i++)
				{
					cv::Vec4i v = lines[i];
					cv::line(m_image, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), cv::Scalar(0, 0, 255));
				}

				std::cout << "LINES SIZE: " << lines.size() << std::endl;




				Corners corners;
				for (unsigned int i = 0; i < lines.size(); i++)
				{
					for (unsigned int j = (i + 1); j < lines.size(); j++)
					{
						cv::Point2f cross = ComputeCross(lines[i], lines[j]);
						if (cross.x >= 0 && cross.y >= 0)
						{
							corners.push_back(cross);
						}
					}
				}


				ClusterCorners(corners, 10);
				for (unsigned int i = 0; i < corners.size(); ++i)
				{
					cv::circle(m_image, corners[i], 7, cv::Scalar(0, 0, 255));
				}

				std::cout << "LINES: " << lines.size() << " - CORNERS: " << corners.size() << std::endl;

				//cv::Mat curve;
				//if (corners.size() == 4)
				//{
				//	curve = cv::Mat(corners);
				//	std::vector<cv::Point2f> approx;

				//	cv::approxPolyDP(curve, approx,
				//		(cv::arcLength(curve, true) * 0.02), true);

				//	int offset = 30;
				//	cv::Rect boundingBox = cv::boundingRect(approx);
				//	boundingBox.x -= offset;
				//	boundingBox.y -= offset;
				//	boundingBox.width += (offset * 2);
				//	boundingBox.height += (offset * 2);

				//	if (boundingBox.contains(m_center))
				//	{
				//		if (approx.size() == 4)
				//		{
				//			m_boundingBox = boundingBox;

				//			cv::Point2f center = cv::Point2f(0, 0);
				//			for (unsigned int i = 0; i < corners.size(); i++)
				//			{
				//				center += corners[i];
				//			}
				//			center *= (1.0 / corners.size());

				//			if (SortCorners(corners, center))
				//			{
				//				m_lost = false;
				//				m_center = center;
				//				m_corners = corners;
				//			}
				//		}
				//	}
				//}

				//// Release the curve
				//curve.release();








				if (m_lost)
				{
					// DEBUG BOUNDING BOX
					cv::rectangle(m_image, m_boundingBox, cv::Scalar(255, 255, 255));
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
			m_center.x = P_EVT.MouseInput.X;
			m_center.y = P_EVT.MouseInput.Y;

			if (P_EVT.MouseInput.isLeftPressed())
			{
				m_chosen = true;
			}
		}

		return false;
	}

	bool Capture::HasChosen()
	{
		return m_chosen;
	}

	bool Capture::IsLost()
	{
		return m_lost;
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

	void Capture::ClusterCorners(Corners p_corners, int p_offset)
	{
		Corners corners;
		while (p_corners.size() > 0)
		{
			// Get a corner
			cv::Point2f corner = p_corners.back();
			p_corners.pop_back();

			// To track the number of corners added
			int numCorners = 1;

			// Calculate the bounding box
			cv::Rect box = cv::Rect((corner.x - p_offset), (corner.y - p_offset), (p_offset * 2), (p_offset * 2));
			cv::rectangle(m_image, box, cv::Scalar(0, 255, 0));

			for (unsigned int i = 0; i < p_corners.size(); ++i)
			{
				if (box.contains(p_corners[i]))
				{
					corner += p_corners[i];
					numCorners++;

					// Remove the element
					p_corners.erase(p_corners.begin() + i);
				}
			}

			// Calculate the center of the corner
			corner *= (1.0 / numCorners);

			// Add the new corner
			corners.push_back(corner);
		}

		// Reset corners
		p_corners.clear();
		p_corners = corners;
	}

	bool Capture::SortCorners(std::vector<cv::Point2f> p_corners, cv::Point2f p_center)
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