#ifndef __CAMERA__CALIBRATION__H__
#define __CAMERA__CALIBRATION__H__

#include "CalibrationSettings.h"
#include "CalibrationParams.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Camera
{

   /**
	* @brief	This class is responsible for the camera calibration
	* You can calibration the camera by holding an odd checkerboard in front of the camera. 
	* More comments are welcome in this class.
	* @author	Alex Hodes
	*/
	class Calibration
	{
		/**
		 * @brief	TODO
		 * @author	Alex Hodes
		 */
		enum State
		{
			DETECTION = 0,
			CAPTURING = 1,
			CALIBRATED = 2
		};

		/**
		 * @brief	TODO
		 * @author	Alex Hodes
		 */
		enum CalibrationFlag
		{
			CALIB_CB_SYMMETRIC_GRID = 1,
			CALIB_CB_ASYMMETRIC_GRID = 2,
			CALIB_CB_CLUSTERING = 4
		};

		/**
		 * @brief	TODO
		 * @author	Alex Hodes
		 * @todo give this type a name
		 */
		enum
		{
			//!< nearest neighbor interpolation
			INTER_NEAREST=CV_INTER_NN,
			//!< bilinear interpolation
			INTER_LINEAR=CV_INTER_LINEAR,
			//!< bicubic interpolation
			INTER_CUBIC=CV_INTER_CUBIC,
			//!< area-based (or super) interpolation
			INTER_AREA=CV_INTER_AREA,
			//!< Lanczos interpolation over 8x8 neighborhood
			INTER_LANCZOS4=CV_INTER_LANCZOS4,
			INTER_MAX=7,
			WARP_INVERSE_MAP=CV_WARP_INVERSE_MAP
		};

	public:
		/**
		 * @brief	Constructor
		 */
		Calibration();

		/**
		 * @brief	Deconstructor
		 */
		~Calibration();

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();
		
	   /**
		* @brief	Comment TODO, Function complete
		*/
		void Start();
		
	private:
		typedef std::vector<cv::Point2f> Corners;
		typedef std::vector<Corners> Contours;
		typedef std::vector<float> PerViewErrors;
		typedef std::vector<cv::Mat> CvMats;
		typedef std::vector<cv::Point3f> Points;
		CalibrationSettings* m_settings;
		CalibrationParams* m_params;
		cv::VideoCapture m_capture;
		unsigned int m_currentFrame;

		/**
		 * @brief	Fetches the next frame into p_image
		 * This is eithe the next webcam frame, the next video frame
		 * or the next image
		 * @param	p_image The image matrix to load into
		 */
		void FetchNextImage(cv::Mat& p_image);

		/**
		 * @brief	Runs the calibration and saves the results
		 * @see		Calibration::RunCalibration
		 * @see		Calibration::SaveParams
		 * @param	p_imageSize The size of the image
		 * @param	p_cameraMatrix The new camera matrix
		 * @param	p_distortionCoefficients The new distortion coefficients
		 * @param	p_contours The detected contours
		 */
		bool RunAndSaveCalibration(cv::Size& p_imageSize, cv::Mat& p_cameraMatrix,
			cv::Mat& p_distortionCoefficients, Contours& p_contours);

		/**
		 * @brief	Executes the actual calibration
		 * @param	p_imageSize The size of the image
		 * @param	p_cameraMatrix The new camera matrix
		 * @param	p_distortionCoefficients The new distortion coefficients
		 * @param	p_contours The detected contours
		 * @param	p_averageReprojectionError The average reprojection error
		 * @param	p_perViewReprojectionErrors The reprojection errors per view
		 * @param	p_rvecs TODO: explain
		 * @param	p_tvecs TODO: explain
		 */
		bool RunCalibration(cv::Size& p_imageSize, cv::Mat& p_cameraMatrix,
			cv::Mat& p_distortionCoefficients, Contours& p_contours,
			double& p_averageReprojectionError, PerViewErrors& p_perViewReprojectionErrors,
			CvMats& p_rvecs, CvMats& p_tvecs);

		/**
		 * @brief	Calculates the corners of the checkerboard image
		 * @param	p_points TODO: explain
		 */
		void CalculateBoardCorners(Points& p_points);

		/**
		 * @brief	Compute reprojection errors
		 * @param	p_cameraMatrix The new camera matrix
		 * @param	p_distortionCoefficients The new distortion coefficients
		 * @param	p_contours The detected contours
		 * @param	p_perViewReprojectionErrors The reprojection errors per view
		 * @param	p_rvecs TODO: explain
		 * @param	p_tvecs TODO: explain
		 * @param	p_points TODO: explain
		 * @return	The average reprojection error
		 */
		double ComputeReprojectionErrors(cv::Mat& p_cameraMatrix,
			cv::Mat& p_distortionCoefficients, Contours& p_contours,
			PerViewErrors& p_perViewReprojectionErrors,
			CvMats& p_rvecs, CvMats& p_tvecs, std::vector<Points>& p_points);

		/**
		 * @brief	Saves the calibration parameres to a file
		 * @param	p_imageSize The size of the image
		 * @param	p_cameraMatrix The new camera matrix
		 * @param	p_distortionCoefficients The new distortion coefficients
		 * @param	p_contours The detected contours
		 * @param	p_averageReprojectionError The average reprojection error
		 * @param	p_perViewReprojectionErrors The reprojection errors per view
		 * @param	p_rvecs TODO: explain
		 * @param	p_tvecs TODO: explain
		 */
		void SaveParams(cv::Size& p_imageSize, cv::Mat& p_cameraMatrix,
			cv::Mat& p_distortionCoefficients, Contours& p_contours,
			double& p_averageReprojectionError, PerViewErrors& p_perViewReprojectionErrors,
			CvMats& p_rvecs, CvMats& p_tvecs);
	};
}

#endif