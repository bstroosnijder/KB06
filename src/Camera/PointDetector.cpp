#include "..\..\include\Camera\PointDetector.h"

namespace Camera
{
	PointDetector::PointDetector(void)
	{
	}

	PointDetector::~PointDetector(void)
	{
	}

	int PointDetector::FindPointsInFrame(cv::Mat p_frame, std::vector<cv::Point2f> p_corners, irr::core::matrix4 p_cameraMatrix, float p_pixelDistance, cv::Size p_sizeHalfed, irr::core::vector3df*& p_startPoints, irr::core::vector3df*& p_endPoints)
	{
		p_cameraMatrix.makeInverse();
		float startX = (p_pixelDistance / p_sizeHalfed.width);
		float startZ = (p_pixelDistance / p_sizeHalfed.height);

		cv::Mat quad = cv::Mat::zeros(300, 300, CV_8U);

		// corners of the destination image
		std::vector<cv::Point2f> quad_pts;
		quad_pts.push_back(cv::Point2f(0, 0));
		quad_pts.push_back(cv::Point2f(quad.cols, 0));
		quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
		quad_pts.push_back(cv::Point2f(0, quad.rows));

		// get transformation matrix
		cv::Mat matrix = cv::getPerspectiveTransform(p_corners, quad_pts);

		// Apply perspective transformation
		cv::warpPerspective(p_frame, quad, matrix, quad.size());
		/*cv::imshow("quadrilateral", quad);
		cv::waitKey(1);*/

		cv::Mat bw;
		cv::cvtColor(quad, bw, CV_BGR2GRAY);
		/*cv::imshow("bw", bw);
		cv::waitKey(1);*/

		cv::blur(bw, bw, cv::Size(3, 3));
		/*cv::imshow("bw+blur", bw);
		cv::waitKey(1);*/

		cv::threshold(bw, bw, 190, 255, cv::THRESH_BINARY);
		/*cv::imshow("bw+blur+treshold", bw);
		cv::waitKey(1);*/

		/*cv::Canny( bw, bw, 100, 200, 3 );
		cv::imshow("bw+blur+treshold+canny", bw);
		cv::waitKey(1);*/

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

			cv::Mat curve = cv::Mat(contours[i]);
			std::vector<cv::Point2f> approx;
			curve.convertTo(curve, cv::Mat(approx).type());
			cv::approxPolyDP(curve, approx, (cv::arcLength(curve, true) * 0.02), true);

			if (approx.size() < 4)
			{
				continue;
			}

			contoursSize++;
			pointContours.push_back(contours[i]);
		}


		if (contoursSize > 0)
		{
			p_startPoints = new irr::core::vector3df[contoursSize];
			p_endPoints = new irr::core::vector3df[contoursSize];

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
					std::cout << i << ") " << approx.size() << std::endl; // Debug how many approxes are in the contour.

					// Define 2 points for begin and end, it does not matter if A or B is the top or lower point.
					cv::Point2f pointA, pointB;

					// Define a skip length. If points are in this range only one of the points will be used.
					int pointSkipLength = 15;

					// Loop through all of the points in the contour
					for (int j = 0; j < approx.size(); j++)
					{
						cv::circle(quad, cv::Point(approx.at(j).x, approx.at(j).y), 3, cv::Scalar(255, 0, 0)); // DUMMY visualizer for all points in the contour.

						// Only set point A If it is not set yet.
						if (pointA.x == 0 && pointA.y == 0)
						{
							pointA.x = approx.at(j).x;
							pointA.y = approx.at(j).y;

							cv::circle(quad, pointA, 4, cv::Scalar(0, 0, 255)); // DUMMY visualizer for point A.
						}
						else
						{
							// If points are within the range we can skip this point.
							if (abs(pointA.x - approx.at(j).x) < pointSkipLength && abs(pointA.y - approx.at(j).y) < pointSkipLength)
							{
								continue;
							}
							else
							{
								// Only set point B if it is not set, yet.
								if (pointB.x == 0 && pointB.y == 0)
								{
									pointB.x = approx.at(j).x;
									pointB.y = approx.at(j).y;

									cv::circle(quad, pointB, 4, cv::Scalar(0, 0, 255)); // DUMMY visualizer for point B.

									// We got point A and B, no need to look further.
									break;
								}
							}
						}
					}

					irr::core::vector3df pointTop;
					irr::core::vector3df pointBottom;

					// Determine which point is top or bottom.
					if (pointA.y > pointB.y)
					{
						pointTop.X = pointA.x * startX;
						pointTop.Y = pointA.y * startZ;
						pointTop.Z = 0.0f;

						pointBottom.X = pointB.x * startX;
						pointBottom.Y = pointB.y * startZ;
						pointBottom.Z = 0.0f;
					}
					else
					{
						pointTop.X = pointB.x * startX;
						pointTop.Y = pointB.y * startZ;
						pointTop.Z = 0.0f;

						pointBottom.X = pointA.x * startX;
						pointBottom.Y = pointA.y * startZ;
						pointBottom.Z = 0.0f;
					}

					p_cameraMatrix.transformVect(pointTop);
					p_cameraMatrix.transformVect(pointBottom);

					p_startPoints[i] = irr::core::vector3df(pointTop.Y, pointTop.Z, pointTop.X);
					p_endPoints[i] = irr::core::vector3df(pointBottom.Y, pointBottom.Z, pointBottom.X);

					// Draw a bounding box around the contour.
					cv::Rect boundingBox = cv::boundingRect(approx);
					cv::rectangle(quad, boundingBox, cv::Scalar(0, 255, 0));
				}

				cv::imshow("bw boundingbox", quad);
			}
		}

		return contoursSize;
	}
}