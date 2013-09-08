#include "Camera/Capture.h"

namespace Camera
{
	Capture::Capture(irr::video::ITexture* p_texture)
	{
		m_capture = cv::VideoCapture(CV_CAP_ANY);
		m_image = cv::Mat();
		m_texture = p_texture;
	}

	Capture::~Capture()
	{
		Cleanup();
	}

	void Capture::Cleanup()
	{
		m_image.release();
		m_capture.release();
	}

	void Capture::Update()
	{
		if (m_capture.isOpened())
		{
			m_capture >> m_image;
			if (!m_image.empty())
			{
				cv::GaussianBlur(m_image, m_image, cv::Size(3, 3), 0);
				cv::cvtColor(m_image, m_image, CV_BGR2BGRA, 4);

				unsigned char* buffer = static_cast<unsigned char*>(m_texture->lock());
				memcpy(buffer, m_image.data, (sizeof(unsigned char) * ((m_image.rows * m_image.cols) * m_image.channels())));
				m_texture->unlock();

				// Show the threshold image
				cv::Mat gray = m_image.clone();
				cv::cvtColor(gray, gray, CV_BGR2GRAY, 1);
				cv::threshold(gray, gray, 80, 255, CV_THRESH_BINARY);
				//cv::imshow("GRAY", gray);

				// Draw contours
				//cv::Mat imgContours(gray.size(), CV_8UC3, cv::Scalar(0, 0, 0));
				cv::Mat imgContours = m_image.clone();
				std::vector<std::vector<cv::Point>> contours;
				cv::MemStorage* storage = new cv::MemStorage();
				cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

				for (unsigned int i = 0; i < contours.size(); ++i)
				{
					if (contours[i].size() >= 4)
					{
						cv::drawContours(imgContours, contours, i, cv::Scalar(0, 0, 255));
					}
				}
				cv::imshow("CONTOURS", imgContours);

				// release
				gray.release();
				imgContours.release();
			}
		}
	}
}