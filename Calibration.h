#ifndef __CALIBRATION__H__
#define __CALIBRATION__H__

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

/**
* @brief	TODO
* @author	Alex Hodes
*/

namespace Camera
{
	class Calibration
	{

		

		enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
		enum InputType {INVALID, CAMERA, VIDEO_FILE, IMAGE_LIST};
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


	private:
		std::string patternToUse;
		cv::Size boardSize;            // The size of the board -> Number of items by width and height
		Pattern calibrationPattern;// One of the Chessboard, circles, or asymmetric circle pattern
		float squareSize;          // The size of a square in your defined unit (point, millimeter,etc).
		int nrFrames;              // The number of frames to use from the input for calibration
		float aspectRatio;         // The aspect ratio
		int delay;                 // In case of a video input
		bool bwritePoints;         //  Write detected feature points
		bool bwriteExtrinsics;     // Write extrinsic parameters
		bool calibZeroTangentDist; // Assume zero tangential distortion
		bool calibFixPrincipalPoint;// Fix the principal point at the center
		bool flipVertical;          // Flip the captured images around the horizontal axis
		std::string outputFileName;      // The name of the file where to write
		bool showUndistorsed;       // Show undistorted images after calibration
		std::string input;               // The input ->
		int cameraID;
		std::vector<std::string> imageList;
		int atImageList;
		cv::VideoCapture inputCapture;
		InputType inputType;
		bool goodInput;
		int flag;


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
			Calibration::Pattern patternType /*= Settings::CHESSBOARD*/);

		/**
		* @brief	TODO
		* @author	Alex Hodes
		*/
		bool RunCalibration( Calibration& s, cv::Size& imageSize, cv::Mat& cameraMatrix, cv::Mat& distCoeffs,
			std::vector<std::vector<cv::Point2f> > imagePoints, std::vector<cv::Mat>& rvecs, std::vector<cv::Mat>& tvecs,
			std::vector<float>& reprojErrs,  double& totalAvgErr);

		/**
		* @brief	TODO
		* @author	Alex Hodes
		*/
		void SaveCameraParams( Calibration& s, cv::Size& imageSize, cv::Mat& cameraMatrix, cv::Mat& distCoeffs,
			const std::vector<cv::Mat>& rvecs, const std::vector<cv::Mat>& tvecs,
			const std::vector<float>& reprojErrs, const std::vector<std::vector<cv::Point2f> >& imagePoints,
			double totalAvgErr );

		/**
		* @brief	TODO
		* @author	Alex Hodes
		*/
		bool RunCalibrationAndSave(Calibration& s, cv::Size imageSize, cv::Mat&  cameraMatrix, cv::Mat& distCoeffs,std::vector<std::vector<cv::Point2f> > imagePoints );

				/**
		* @brief	Added
		* @author	Alex Hodes
		*/
		void Write(cv::FileStorage& fs);

		/**
		* @brief	Added
		* @author	Alex Hodes
		*/
		void Read(const cv::FileNode& node);

		/**
		* @brief	Added
		* @author	Alex Hodes
		*/
		void Interprate();

		/**
		* @brief	Added
		* @author	Alex Hodes
		*/
		cv::Mat NextImage();

		/**
		* @brief	Added
		* @author	Alex Hodes
		*/
		bool ReadStringList( const std::string& filename, std::vector<std::string>& l );

		/**
		*@brief		Added
		*@author	Alex Hodes
		*/
		bool getGoodInput();
	};
}

#endif