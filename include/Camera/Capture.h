#ifndef __CAMERA__CAPTURE__H__
#define __CAMERA__CAPTURE__H__

#include <irrlicht.h>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <vector>
#include <list>

namespace Camera
{
	/**
	 * @brief	test
	 * @author	Bas Stroosnijder
	 */
	class Capture : public irr::IEventReceiver
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
		void Update();

		/**
		 * @brief	Handles input
		 * @param	p_evt The event received
		 * @return	Has the event been completely handled
		 */
		bool OnEvent(const irr::SEvent& p_evt);

		/**
		 * @brief	Converts and returns the projection matrix
		 * @return	The new projection matrix
		 */
		irr::core::matrix4 GetProjectionMatrix();

		/**
		 * @brief	test
		 * @return	If the surface has been chosen
		 */
		bool HasChosen();

		/**
		 * @brief	test
		 * @return	If the surface has been lost
		 */
		bool IsLost();

	private:
		typedef std::vector<cv::Point2f> Corners;
		irr::video::ITexture* m_texture;
		cv::VideoCapture m_capture;

		bool m_chosen;
		bool m_lost;
		cv::Size m_size;
		cv::Point2f m_center;
		cv::Rect m_boundingBox;
		Corners m_corners;
		cv::Scalar m_color;

		cv::Mat m_image;
		cv::Mat m_matrix;

		void CopyToTexture();
		cv::Point2f ComputeCross(cv::Vec4i p_vec1, cv::Vec4i p_vec2);
		bool SortCorners(Corners p_corners, cv::Point2f p_center);
	};
}

#endif