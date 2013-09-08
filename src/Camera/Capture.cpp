#include "Camera/Capture.h"

namespace Camera
{
	Capture::Capture(irr::video::ITexture* p_texture)
	{
		m_capture = cvCreateCameraCapture(CV_CAP_ANY);
		m_image = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 4);
		m_texture = p_texture;
	}

	Capture::~Capture()
	{
		Cleanup();
	}

	void Capture::Cleanup()
	{
		cvReleaseImage(&m_image);
		cvReleaseCapture(&m_capture);
	}

	void Capture::UpdateTexture()
	{
		IplImage* frame = cvQueryFrame(m_capture);

		// The initialization of the camera might take a while, lets check for that
		if (frame != NULL)
		{
			// The image has to have an alpha channel or Irrlicht won't be able to work with it
			cvCvtColor(frame, m_image, CV_BGR2BGRA);

			char* buffer = static_cast<char*>(m_texture->lock());
			memcpy(buffer, m_image->imageData, m_image->imageSize);
			m_texture->unlock();
		}
	}
}