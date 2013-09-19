#include "Camera/CalibrationParams.h"

namespace Camera
{
	CalibrationParams::CalibrationParams(std::string p_filename)
	{
		m_filename = p_filename;
		cv::FileStorage storage = cv::FileStorage(m_filename, cv::FileStorage::READ);
		if (storage.isOpened())
		{
			storage["number_of_frames"] >> m_numberOfFrames;
			storage["image_width"] >> m_imageWidth;
			storage["image_height"] >> m_imageHeight;
			storage["board_width"] >> m_boardWidth;
			storage["board_height"] >> m_boardHeight;
			storage["square_size"] >> m_squareSize;
			storage["aspact_ratio"] >> m_aspectRatio;
			storage["flag"] >> m_flag;
			storage["camera_matrix"] >> m_cameraMatrix;
			storage["distortion_coefficients"] >> m_distortionCoefficients;
			storage["average_reprojection_error"] >> m_averageReprojectionError;
			storage["per_view_reprojection_errors"] >> m_perViewReprojectionErrors;
			storage["extrinsic_arameters"] >> m_extrinsicParameters;
			storage["image_points"] >> m_imagePoints;
		}

		// Release
		storage.release();
	}

	CalibrationParams::~CalibrationParams()
	{
		Cleanup();
	}

	void CalibrationParams::Cleanup()
	{
		m_cameraMatrix.release();
		m_distortionCoefficients.release();
		m_perViewReprojectionErrors.release();
		m_extrinsicParameters.release();
		m_imagePoints.release();
	}

	void CalibrationParams::Save()
	{
		cv::FileStorage storage = cv::FileStorage(m_filename, cv::FileStorage::WRITE);
		if (storage.isOpened())
		{
			// Get the time
			char time[1024];
			std::time_t now = std::time(NULL);
			struct tm* localTime = std::localtime(&now);
			strftime(time, sizeof(time), "%c", localTime);

			storage << "calibration_timestamp" << time;
			storage << "number_of_frames" << m_numberOfFrames;
			storage << "image_width" << m_imageWidth;
			storage << "image_height" << m_imageHeight;
			storage << "board_width" << m_boardWidth;
			storage << "board_height" << m_boardHeight;
			storage << "square_size" << m_squareSize;
			storage << "aspact_ratio" << m_aspectRatio;
			storage << "flag" << m_flag;
			storage << "camera_matrix" << m_cameraMatrix;
			storage << "distortion_coefficients" << m_distortionCoefficients;
			storage << "average_reprojection_error" << m_averageReprojectionError;
			storage << "per_view_reprojection_errors" << m_perViewReprojectionErrors;
			storage << "extrinsic_arameters" << m_extrinsicParameters;
			storage << "image_points" << m_imagePoints;
		}

		storage.release();
	}

	int CalibrationParams::GetNumberOfFrames()
	{
		return m_numberOfFrames;
	}

	void CalibrationParams::SetNumberOfFrames(int p_numberOfFrames)
	{
		m_numberOfFrames = p_numberOfFrames;
	}

	int CalibrationParams::GetImageWidth()
	{
		return m_imageWidth;
	}

	void CalibrationParams::SetImageWidth(int p_imageWidth)
	{
		m_imageWidth = p_imageWidth;
	}

	int CalibrationParams::GetImageHeight()
	{
		return m_imageHeight;
	}

	void CalibrationParams::SetImageHeight(int p_imageHeight)
	{
		m_imageHeight = p_imageHeight;
	}

	int CalibrationParams::GetBoardWidth()
	{
		return m_boardWidth;
	}

	void CalibrationParams::SetBoardWidth(int p_boardWidth)
	{
		m_boardWidth = p_boardWidth;
	}

	int CalibrationParams::GetBoardHeight()
	{
		return m_boardHeight;
	}

	void CalibrationParams::SetBoardHeight(int p_boardHeight)
	{
		m_boardHeight = p_boardHeight;
	}

	float CalibrationParams::GetSquareSize()
	{
		return m_squareSize;
	}

	void CalibrationParams::SetSquareSize(float p_squareSize)
	{
		m_squareSize = p_squareSize;
	}

	float CalibrationParams::GetAspectRatio()
	{
		return m_aspectRatio;
	}

	void CalibrationParams::SetAspectRatio(float p_aspectRatio)
	{
		m_aspectRatio = p_aspectRatio;
	}

	int CalibrationParams::GetFlag()
	{
		return m_flag;
	}

	void CalibrationParams::SetFlag(int p_flag)
	{
		m_flag = p_flag;
	}

	cv::Mat CalibrationParams::GetCameraMatrix()
	{
		return m_cameraMatrix;
	}

	void CalibrationParams::SetCameraMatrix(cv::Mat p_cameraMatrix)
	{
		m_cameraMatrix = p_cameraMatrix;
	}

	cv::Mat CalibrationParams::GetDistortionCoefficients()
	{
		return m_distortionCoefficients;
	}

	void CalibrationParams::SetDistortionCoefficients(cv::Mat p_distortionCoefficients)
	{
		m_distortionCoefficients = p_distortionCoefficients;
	}

	double CalibrationParams::GetAverageReprojectionError()
	{
		return m_averageReprojectionError;
	}

	void CalibrationParams::SetAverageReprojectionError(double p_averageReprojectionError)
	{
		m_averageReprojectionError = p_averageReprojectionError;
	}

	cv::Mat CalibrationParams::GetPerViewReprojectionErrors()
	{
		return m_perViewReprojectionErrors;
	}

	void CalibrationParams::SetPerViewReprojectionErrors(cv::Mat p_perViewReprojectionErrors)
	{
		m_perViewReprojectionErrors = p_perViewReprojectionErrors;
	}

	cv::Mat CalibrationParams::GetExtrinsicParameters()
	{
		return m_extrinsicParameters;
	}

	void CalibrationParams::SetExtrinsicParameters(cv::Mat p_extrinsicParameters)
	{
		m_extrinsicParameters = p_extrinsicParameters;
	}

	cv::Mat CalibrationParams::GetImagePoints()
	{
		return m_imagePoints;
	}

	void CalibrationParams::SetImagePoints(cv::Mat p_imagePoints)
	{
		m_imagePoints = p_imagePoints;
	}
}