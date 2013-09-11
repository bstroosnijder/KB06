#ifndef __CALIBRATION__H__
#define __CALIBRATION__H__

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include "CalibrationSettings.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>



namespace Camera
{

   /**
	* @brief	TODO
	* @author	Alex Hodes
	*/
	class Calibration
	{
		
		enum { DETECTION = 0, CAPTURING = 1, CALIBRATED = 2 };
		enum { CALIB_CB_SYMMETRIC_GRID = 1, CALIB_CB_ASYMMETRIC_GRID = 2,
			CALIB_CB_CLUSTERING = 4 };
		enum
		{
			INTER_NEAREST=CV_INTER_NN, //!< nearest neighbor interpolation
			INTER_LINEAR=CV_INTER_LINEAR, //!< bilinear interpolation
			INTER_CUBIC=CV_INTER_CUBIC, //!< bicubic interpolation
			INTER_AREA=CV_INTER_AREA, //!< area-based (or super) interpolation
			INTER_LANCZOS4=CV_INTER_LANCZOS4, //!< Lanczos interpolation over 8x8 neighborhood
			INTER_MAX=7,
			WARP_INVERSE_MAP=CV_WARP_INVERSE_MAP
		};

	public:
		Calibration();
		
		/**
		* @brief	TODO
		* @author	Alex Hodes
		*/
		int Start(int argc, char* argv[]);
		
		//private:

		/**
		* @brief	Added
		* @author	Alex Hodes
		*/
		double ComputeReprojectionErrors( const std::vector<std::vector<cv::Point3f> >& objectPoints,
				const std::vector<std::vector<cv::Point2f> >& imagePoints,
				const std::vector<cv::Mat>& rvecs, const std::vector<cv::Mat>& tvecs,
				const cv::Mat& cameraMatrix , const cv::Mat& distCoeffs,
				std::vector<float>& perViewErrors);

		/**
		* @brief	Added
		* @author	Alex Hodes
		*/
		void CalcBoardCornerPositions(cv::Size boardSize, float squareSize, std::vector<cv::Point3f>& corners,
				CalibrationSettings::Pattern patternType /*= Settings::CHESSBOARD*/);

		/**
		* @brief	TODO
		* @author	Alex Hodes
		*/
		bool RunCalibration( CalibrationSettings& s, cv::Size& imageSize, cv::Mat& cameraMatrix, cv::Mat& distCoeffs,
				std::vector<std::vector<cv::Point2f> > imagePoints, std::vector<cv::Mat>& rvecs, std::vector<cv::Mat>& tvecs,
				std::vector<float>& reprojErrs,  double& totalAvgErr);

		/**
		* @brief	TODO
		* @author	Alex Hodes
		*/
		void SaveCameraParams( CalibrationSettings& s, cv::Size& imageSize, cv::Mat& cameraMatrix, cv::Mat& distCoeffs,
				const std::vector<cv::Mat>& rvecs, const std::vector<cv::Mat>& tvecs,
				const std::vector<float>& reprojErrs, const std::vector<std::vector<cv::Point2f> >& imagePoints,
				double totalAvgErr );

		/**
		* @brief	TODO
		* @author	Alex Hodes
		*/
		bool RunCalibrationAndSave(CalibrationSettings& s, cv::Size imageSize, cv::Mat&  cameraMatrix, cv::Mat& distCoeffs,std::vector<std::vector<cv::Point2f> > imagePoints );

		/**
		*@brief		Help
		*@author	Alex Hodes
		*/
		void Help();
	};
}

#endif