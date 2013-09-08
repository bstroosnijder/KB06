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

	void Capture::UpdateTexture()
	{
		if (m_capture.isOpened())
		{
			m_capture >> m_image;
			if (!m_image.empty())
			{
				cv::cvtColor(m_image, m_image, CV_BGR2BGRA, 4);

				unsigned char* buffer = static_cast<unsigned char*>(m_texture->lock());
				memcpy(buffer, m_image.data, (sizeof(unsigned char) * ((m_image.rows * m_image.cols) * m_image.channels())));
				m_texture->unlock();
			}
		}
	}
}