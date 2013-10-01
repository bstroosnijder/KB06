#ifndef __CAMERA__CAPTURE__H__
#define __CAMERA__CAPTURE__H__

#include "CalibrationParams.h"
#include <irrlicht.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <cmath>

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
		 * @param	p_runInOwnThread If the capturer should run in it's own thread
		 * @param	p_texture A reference to the texture to update with the camera
		 */
		Capture(bool p_runInOwnThread, irr::video::ITexture* p_texture);

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
		 * @brief	Starts the capture thread
		 */
		void Start();

		/**
		 * @brief	Handles input
		 * @param	p_evt The event received
		 * @return	Has the event been completely handled
		 */
		bool OnEvent(const irr::SEvent& P_EVT);

		/**
		 * @brief	Converts and returns the transform matrix
		 * @param	p_cameraProjection The camera projection matrix to use for multiplications
		 * @return	The new projection matrix
		 */
		irr::core::matrix4 GetTransformMatrix(
			irr::core::matrix4 p_cameraProjection);

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

		/**
		 * @brief	Gets the fov
		 * @return	The fov
		 */
		float GetFox();

		/**
		 * @brief	Sets the fov
		 * @param	p_fov The new fov
		 */
		void SetFov(float p_fov);


		/**
		 * @brief	test
		 * @return	The distance of the camera in pixels
		 */
		float GetPixelDistance();

	private:
		typedef std::vector<cv::Point3f> Points3D;
		typedef std::vector<cv::Point2f> Corners;
		irr::video::ITexture* m_texture;
		bool m_runInOwnThread;
		CalibrationParams* m_params;
		cv::VideoCapture m_capture;

		float m_fov;

		bool m_running;
		std::thread* m_thread;
		std::mutex* m_mutex;


		bool m_chosen;
		bool m_lost;
		cv::Size m_size;
		cv::Size m_sizeHalfed;
		cv::Point2f m_center;
		float m_pixelDistance;
		cv::Rect m_boundingBox;
		cv::Scalar m_color;

		Points3D m_points3D;
		Corners m_corners;
		cv::Mat m_poseRotation;
		cv::Mat m_poseTranslation;

		cv::Mat m_image;
		//cv::Mat m_matrix;

		/**
		 * @brief	Locks the mutex with this thread
		 */
		void Lock();

		/**
		 * @brief	Unlocks the mutex with this thread
		 */
		void Unlock();

		/**
		 * @brief	Updates the texture to the latest frame of the camera
		 */
		void Work();

		/**
		 * @brief	Thread worker
		 * @see		Capture::Work
		 */
		void Worker();

		/**
		 * @brief	Fetches a image from the capture and undistort the image
		 */
		void CaptureAndUndistort();

		/**
		 * @brief	Copies the image to the irrlicht texture
		 */
		void CopyToTexture();

		/**
		 * @brief	Compues the intersections of two lines
		 * @param	p_vec1 The first line
		 * @param	p_vec2 The second line
		 * @return	The computed intersection
		 */
		cv::Point2f ComputeCross(cv::Vec4i p_vec1, cv::Vec4i p_vec2);

		/**
		 * @brief	Sorts the corners so that they are lt, tr, br, bl
		 * @param	p_corners The list of corners
		 * @param	p_center The center around which to sort the corners
		 * @return	Whether or not the corners were correctly sorted
		 */
		bool SortCorners(Corners p_corners, cv::Point2f p_center);
	};
}

#endif