#include "..\..\include\Camera\PointDetector.h"

namespace Camera
{
	PointDetector::PointDetector(void)
	{
	}


	PointDetector::~PointDetector(void)
	{
	}

	void PointDetector::FindPointsInFrame(cv::Mat frame, std::vector<cv::Point2f> corners)
	{
		cv::Mat quad = cv::Mat::zeros(300, 300, CV_8U);

		// corners of the destination image
		std::vector<cv::Point2f> quad_pts;
		quad_pts.push_back(cv::Point2f(0, 0));
		quad_pts.push_back(cv::Point2f(quad.cols, 0));
		quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
		quad_pts.push_back(cv::Point2f(0, quad.rows));

		// get transformation matrix
		cv::Mat matrix = cv::getPerspectiveTransform(corners, quad_pts);

		// Apply perspective transformation
		cv::warpPerspective(frame, quad, matrix, quad.size());
		cv::imshow("quadrilateral", quad);
		cv::waitKey(1);

		cv::Mat bw;
		cv::cvtColor(quad, bw, CV_BGR2GRAY);
		cv::blur(bw, bw, cv::Size(3, 3));
		cv::threshold(bw, bw, 120, 255, cv::THRESH_BINARY);

		// Find contours in the black & white image.
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(bw, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(10, 10));

		int contoursSize = 0;
		std::vector<std::vector<cv::Point>> pointContours;

		// Determine if we can skip certain contours.
		for (int i = 0; i < contours.size(); i++)
		{
			double areaSize = std::fabs(cv::contourArea(contours[i]));

			// The pencils / markers have an area size around 200-500px.
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
					std::cout << i << ") " << approx.size() << std::endl;
					std::cout << i << ") a: 0, x: " << approx.at(0).x << ", y: "<< approx.at(0).y << std::endl;
					std::cout << i << ") a: 1, x: " << approx.at(1).x << ", y: "<< approx.at(1).y << std::endl;
					std::cout << i << ") a: 2, x: " << approx.at(2).x << ", y: "<< approx.at(2).y << std::endl;
					std::cout << i << ") a: 3, x: " << approx.at(3).x << ", y: "<< approx.at(3).y << std::endl;

					for (int i = 0; i < approx.size(); i++)
					{
						cv::circle(quad, cv::Point(approx.at(i).x, approx.at(i).y), 3, cv::Scalar(255, 0, 0));
					}
					//cv::circle(quad, cv::Point(approx.at(0).x, approx.at(0).y), 3, cv::Scalar(255, 0, 0));

					//cv::circle(quad, cv::Point(approx.at(0).x, approx.at(0).y), 3, cv::Scalar(255, 0, 0));
					//cv::circle(quad, cv::Point(approx.at(1).x, approx.at(1).y), 3, cv::Scalar(0, 255, 0));
					//cv::circle(quad, cv::Point(approx.at(2).x, approx.at(2).y), 3, cv::Scalar(0, 0, 255));
					//cv::circle(quad, cv::Point(approx.at(3).x, approx.at(3).y), 3, cv::Scalar(255, 0, 255));

					m_startPoints[i].X = 1;
					m_startPoints[i].Y = 0;
					m_startPoints[i].Z = 1;

					m_endPoints[i].X = 1;
					m_endPoints[i].Y = 0;
					m_endPoints[i].Z = 1;

					// Draw a bounding box around the contour.
					cv::Rect boundingBox = cv::boundingRect(approx);
					cv::rectangle(quad, boundingBox, cv::Scalar(0, 255, 0));
				}

				cv::imshow("bw boundingbox", quad);
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