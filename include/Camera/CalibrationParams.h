#ifndef __CAMERA__CALIBRATIONPARAMS__H__
#define __CAMERA__CALIBRATIONPARAMS__H__

#include <opencv\cv.h>
#include <string>
#include <time.h>

namespace Camera
{
	/**
	 * @brief	Helper class for loading and saving of calibration parameters
	 * @author	Bas Stroosnijder
	 */
	class CalibrationParams
	{
	public:
		/**
		 * @brief	Constructor
		 * @param	p_filename The name of the file to load and to save to
		 */
		CalibrationParams(std::string p_filename);

		/**
		 * @brief	Destructor
		 * @see		Capture::Cleanup
		 */
		~CalibrationParams();

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();

		/**
		 * @brief	Save data to file
		 */
		void Save();

		/**
		 * @brief	The number of frames
		 * @return	The number of frames
		 */
		int GetNumberOfFrames();

		/**
		 * @brief	The number of frames
		 * @param	p_numberOfFrames The number of frames
		 */
		void SetNumberOfFrames(int p_numberOfFrames);

		/**
		 * @brief	The image width
		 * @return	The image width
		 */
		int GetImageWidth();

		/**
		 * @brief	The image width
		 * @param	p_imageWidth The image width
		 */
		void SetImageWidth(int p_imageWidth);

		/**
		 * @brief	The image height
		 * @return	The image height
		 */
		int GetImageHeight();

		/**
		 * @brief	The image height
		 * @param	p_imageHeight The image height
		 */
		void SetImageHeight(int p_imageHeight);

		/**
		 * @brief	The board width
		 * @return	The board width
		 */
		int GetBoardWidth();

		/**
		 * @brief	The board width
		 * @param	p_boardWidth The board width
		 */
		void SetBoardWidth(int p_boardWidth);

		/**
		 * @brief	The board height
		 * @return	The board height
		 */
		int GetBoardHeight();

		/**
		 * @brief	The board width
		 * @param	p_boardHeight The board width
		 */
		void SetBoardHeight(int p_boardHeight);

		/**
		 * @brief	The square size
		 * @return	The square size
		 */
		float GetSquareSize();

		/**
		 * @brief	The square size
		 * @param	p_squareSize The square size
		 */
		void SetSquareSize(float p_squareSize);

		/**
		 * @brief	The aspect ratio
		 * @return	The aspect ratio
		 */
		float GetAspectRatio();

		/**
		 * @brief	The aspect ratio
		 * @param	p_aspectRatio The aspect ratio
		 */
		void SetAspectRatio(float p_aspectRatio);

		/**
		 * @brief	The flag
		 * @return	The flag
		 */
		int GetFlag();

		/**
		 * @brief	The flag
		 * @param	p_flag The flag
		 */
		void SetFlag(int p_flag);

		/**
		 * @brief	The camera matrix
		 * @return	The camera matrix
		 */
		cv::Mat GetCameraMatrix();

		/**
		 * @brief	The camera matrix
		 * @param	p_cameraMatrix The camera matrix
		 */
		void SetCameraMatrix(cv::Mat p_cameraMatrix);

		/**
		 * @brief	The distortion coefficients
		 * @return	The distortion coefficients
		 */
		cv::Mat GetDistortionCoefficients();

		/**
		 * @brief	The distortion coefficients
		 * @param	p_distortionCoefficients The distortion coefficients
		 */
		void SetDistortionCoefficients(cv::Mat p_distortionCoefficients);

		/**
		 * @brief	The average reprojection error
		 * @return	The average reprojection error
		 */
		double GetAverageReprojectionError();

		/**
		 * @brief	The average reprojection error
		 * @param	p_averageReprojectionError The average reprojection error
		 */
		void SetAverageReprojectionError(double p_averageReprojectionError);

		/**
		 * @brief	The per view reprojection errors
		 * @return	The per view reprojection errors
		 */
		cv::Mat GetPerViewReprojectionErrors();

		/**
		 * @brief	The per view reprojection errors
		 * @param	p_perViewReprojectionErrors The per view reprojection errors
		 */
		void SetPerViewReprojectionErrors(cv::Mat p_perViewReprojectionErrors);

		/**
		 * @brief	The extrinsic parameters
		 * @return	The extrinsic parameters
		 */
		cv::Mat GetExtrinsicParameters();

		/**
		 * @brief	The extrinsic parameters
		 * @param	p_extrinsicParameters The extrinsic parameters
		 */
		void SetExtrinsicParameters(cv::Mat p_extrinsicParameters);

		/**
		 * @brief	The image points
		 * @return	The image points
		 */
		cv::Mat GetImagePoints();

		/**
		 * @brief	The board points
		 * @param	p_imagePoints The board points
		 */
		void SetImagePoints(cv::Mat p_imagePoints);

	private:
		std::string m_filename;
		int m_numberOfFrames;
		int m_imageWidth;
		int m_imageHeight;
		int m_boardWidth;
		int m_boardHeight;
		float m_squareSize;
		float m_aspectRatio;
		int m_flag;
		cv::Mat m_cameraMatrix;
		cv::Mat m_distortionCoefficients;
		double m_averageReprojectionError;
		cv::Mat m_perViewReprojectionErrors;
		cv::Mat m_extrinsicParameters;
		cv::Mat m_imagePoints;
	};
}

#endif