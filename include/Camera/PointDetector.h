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
		 * @param	frame The frame to capture points in
		 * @param	corners Determines the rotation of the frame
		 * @param   p_startPoints A pointer to a vector3df array to store start points.
		 * @param   p_endPoints A pointer to a vector3df array to store end points.
		 */
		void FindPointsInFrame(cv::Mat frame, std::vector<cv::Point2f> corners, irr::core::vector3df* p_startPoints, irr::core::vector3df* p_endPoints);
	};

}

#endif