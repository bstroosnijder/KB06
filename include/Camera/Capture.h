#ifndef __CAMERA__CAPTURE__H__
#define __CAMERA__CAPTURE__H__

#include <irrlicht.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>

namespace Camera
{
	/**
	 * @brief	test
	 * @author	Bas Stroosnijder
	 */
	class Capture
	{
	public:
		/**
		 * @brief	Constructor
		 * @param	p_texture A reference to the texture to update with the camera
		 */
		Capture(irr::video::ITexture* p_texture);

		/**
		 * @brief	Destructor
		 * @see		Capture::Cleanup
		 */
		~Capture();

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();

		/**
		 * @brief	Updates the texture to the latest frame of the camera
		 */
		void UpdateTexture();

	private:
		CvCapture* m_capture;
		IplImage* m_image;
		irr::video::ITexture* m_texture;
	};
}

#endif