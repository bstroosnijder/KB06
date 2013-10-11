#include "..\..\include\Camera\PointDetector.h"

namespace Camera
{
	PointDetector::PointDetector(void)
	{
	}


	PointDetector::~PointDetector(void)
	{
	}

	void PointDetector::FindPointsInFrame(cv::Mat frame)
	{
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(frame, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(10, 10));

		int contoursSize = 0;
		std::vector<std::vector<cv::Point>> pointContours;

		// Determine if we can skip certain contours.
		for (int i = 0; i < contours.size(); i++)
		{
			double areaSize = std::fabs(cv::contourArea(contours[i]));

			// Skip contours with an area smaller than 100px to avoid noise and contours with an area larger than 1000px to skip large objects.
			if (areaSize < 100 || areaSize > 1000)
			{
				continue;
			}

			contoursSize++;
			pointContours.push_back(contours[i]);
		}
		

		if (contoursSize > 0)
		{
			m_startPoints = new irr::core::vector3df[contoursSize];
			m_endPoints = new irr::core::vector3df[contoursSize];

			for (int i = 0; i < contoursSize; i++)
			{
				cv::Mat curve = cv::Mat(pointContours[i]);
				std::vector<cv::Point2f> approx;
				// Convert from std::vector<cv::Point> to Corners
				curve.convertTo(curve, cv::Mat(approx).type());

				cv::approxPolyDP(curve, approx, (cv::arcLength(curve, true) * 0.02), true);

				// Only use approx when it has at least 4 points.
				if (approx.size() >= 4)
				{


					m_startPoints[i].X = 1;
					m_startPoints[i].Y = 0;
					m_startPoints[i].Z = 1;

					m_endPoints[i].X = 1;
					m_endPoints[i].Y = 0;
					m_endPoints[i].Z = 1;

					// Draw a bounding box around the contour.
					cv::Rect boundingBox = cv::boundingRect(approx);
					cv::rectangle(frame, boundingBox, cv::Scalar(0, 255, 0));
				}
			}
		}
		else
		{
			m_startPoints = NULL;
			m_endPoints = NULL;
		}
	}

	irr::core::vector3df* PointDetector::GetStartPoints()
	{
		return m_startPoints;
	}

	irr::core::vector3df* PointDetector::GetEndPoints()
	{
		return m_endPoints;
	}
}