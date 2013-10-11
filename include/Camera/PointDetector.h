#ifndef __CAMERA__POINTDETECTOR__H__
#define __CAMERA__POINTDETECTOR__H__

#include <opencv/cv.h>
#include <irrlicht.h>

namespace Camera
{
	class PointDetector
	{
	public:
		PointDetector(void);
		~PointDetector(void);

		void FindPointsInFrame(cv::Mat frame);
		
		irr::core::vector3df* GetStartPoints();
		irr::core::vector3df* GetEndPoints();

	private:
		irr::core::vector3df* m_startPoints;
		irr::core::vector3df* m_endPoints;
	};

}

#endif