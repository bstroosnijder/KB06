#ifndef __CAMERA__POINTDETECTOR__H__
#define __CAMERA__POINTDETECTOR__H__

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <irrlicht.h>
#include <vector>
#include <list>

namespace Camera
{
	class PointDetector
	{
	public:
		PointDetector(void);
		~PointDetector(void);

		void FindPointsInFrame(cv::Mat frame, std::vector<cv::Point2f> corners);
		
		irr::core::vector3df* GetStartPoints();
		irr::core::vector3df* GetEndPoints();

	private:
		irr::core::vector3df* m_startPoints;
		irr::core::vector3df* m_endPoints;
	};

}

#endif