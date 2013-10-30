#ifndef __CAMERA__POINTDETECTOR__H__
#define __CAMERA__POINTDETECTOR__H__

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <irrlicht.h>
#include <vector>
#include <list>

namespace Camera
{
	/**
	* @brief	Detect start and end points of path markers in a frame.
	* @author	Leon van Egmond
	*/
	class PointDetector
	{
	public:
		/**
		* @brief	Constructor
		*/
		PointDetector(void);

		/**
		* @brief	Destructor
		*/
		~PointDetector(void);

		/**
		* @brief	Finds start and end points of path markers in a frame and sets the m_startPoints and m_endPoints point arrays
		* @param	p_frame The frame to capture points in
		* @param	p_corners Determines the rotation of the frame
		* @param	p_cameraMatrix The camera matrix for multiplying with the points.
		* @param	p_startPoints A pointer to a vector3df array to store start points.
		* @param	p_endPoints A pointer to a vector3df array to store end points.
		* @return	Returns the amount of detected points.
		*/
		int FindPointsInFrame(cv::Mat p_frame, std::vector<cv::Point2f> p_corners,
				irr::core::matrix4 p_cameraMatrix, 
				float p_pixelDistance, cv::Size p_sizeHalfed, 
				irr::core::vector3df*& p_startPoints, 
				irr::core::vector3df*& p_endPoints);
	};

}

#endif