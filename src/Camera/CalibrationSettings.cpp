#include "Camera\CalibrationSettings.h"

namespace Camera
{
	CalibrationSettings::CalibrationSettings(std::string p_filename)
	{
		m_filename = p_filename;
		m_isOpenedAndGood = true;
		cv::FileStorage storage = cv::FileStorage(m_filename, cv::FileStorage::READ);
		if (storage.isOpened())
		{
			cv::FileNode settings = storage["settings"];
			settings["board_width"] >> m_boardWidth;
			settings["board_height"] >> m_boardHeight;
			settings["square_size"] >> m_squareSize;

			std::string calibrationPattern;
			settings["calibration_pattern"] >> calibrationPattern;
			m_calibrationPattern = Pattern::NOT_EXISTING;
			if (!calibrationPattern.compare("CHESSBOARD"))
			{
				m_calibrationPattern = Pattern::CHESSBOARD;
			}
			else if (!calibrationPattern.compare("CIRCLES_GRID"))
			{
				m_calibrationPattern = Pattern::CIRCLES_GRID;
			}
			else if (!calibrationPattern.compare("ASYMMETRIC_CIRCLES_GRID"))
			{
				m_calibrationPattern = Pattern::ASYMMETRIC_CIRCLES_GRID;
			}

			std::string inputType;
			settings["input_type"] >> inputType;
			m_inputType = InputType::INVALID;
			if (inputType >= "0" && inputType <= "9")
			{
				m_inputType = InputType::CAMERA;
				std::stringstream ss(inputType);
				ss >> m_cameraID;
			}
			else
			{
				if (IsImageList(inputType))
				{
					m_inputType = InputType::IMAGE_LIST;
					m_numberOfFrames = (m_numberOfFrames <= static_cast<int>(m_imageList.size()))
						? m_numberOfFrames
						: m_imageList.size();
				}
				else
				{
					m_inputType = InputType::VIDEO_FILE;
					m_videoFile = inputType;
				}
			}

			settings["input_flip_horizontal"] >> m_inputFlipHorizontal;
			settings["input_delay"] >> m_inputDelay;
			settings["number_of_frames"] >> m_numberOfFrames;
			settings["aspect_ratio"] >> m_aspactRatio;
			settings["assume_zero_tangential_distortion"] >> m_assumeZeroTangentialDistortion;
			settings["assume_principal_point_center"] >> m_assumePrincipalPointCenter;
			settings["output_filename"] >> m_outputFilename;
			settings["output_detect_feature_points"] >> m_outputDetectFeaturePoints;
			settings["output_extrinsic_parameters"] >> m_outputExtrinsicParameters;
			settings["show_undistorted_image"] >> m_showUndistortedImage;

			m_flag = 0;
			if (m_aspactRatio)
			{
				m_flag |= CV_CALIB_FIX_ASPECT_RATIO;
			}
			if (m_assumeZeroTangentialDistortion)
			{
				m_flag |= CV_CALIB_ZERO_TANGENT_DIST;
			}
			if (m_assumePrincipalPointCenter)
			{
				m_flag |= CV_CALIB_FIX_PRINCIPAL_POINT;
			}
		}
		else
		{
			m_isOpenedAndGood = false;
		}

		// Release
		storage.release();
	}

	CalibrationSettings::~CalibrationSettings()
	{
		Cleanup();
	}

	void CalibrationSettings::Cleanup()
	{
	}

	bool CalibrationSettings::IsImageList(std::string p_filename)
	{
		bool isImageList = false;
		cv::FileStorage storage = cv::FileStorage(p_filename, cv::FileStorage::READ);
		if (storage.isOpened())
		{
			cv::FileNode node = storage.getFirstTopLevelNode();
			if (node.type() == cv::FileNode::SEQ)
			{
				isImageList = true;

				cv::FileNodeIterator it;
				for (it = node.begin(); it != node.end(); ++it)
				{
					m_imageList.push_back(static_cast<std::string>((*it)));
				}
			}
		}

		// Release
		storage.release();
		return isImageList;
	}

	void CalibrationSettings::Save()
	{
		cv::FileStorage storage = cv::FileStorage(m_filename, cv::FileStorage::WRITE);
		if (storage.isOpened())
		{
			storage << "{";
			storage << "board_width" << m_boardWidth;
			storage << "board_height" << m_boardHeight;
			storage << "square_size" << m_squareSize;
			storage << "calibration_pattern" << m_calibrationPattern;
			storage << "input_type" << m_inputType;
			storage << "input_flip_horizontal" << m_inputFlipHorizontal;
			storage << "input_delay" << m_inputDelay;
			storage << "number_of_frames" << m_numberOfFrames;
			storage << "aspect_ratio" << m_aspactRatio;
			storage << "assume_zero_tangential_distortion" << m_assumeZeroTangentialDistortion;
			storage << "assume_principal_point_center" << m_assumePrincipalPointCenter;
			storage << "output_filename" << m_outputFilename;
			storage << "output_detect_feature_points" << m_outputDetectFeaturePoints;
			storage << "output_extrinsic_parameters" << m_outputExtrinsicParameters;
			storage << "show_undistorted_image" << m_showUndistortedImage;
			storage << "}";
		}

		// Release
		storage.release();
	}

	bool CalibrationSettings::GetIsOpenedAndGood()
	{
		return m_isOpenedAndGood;
	}

	int CalibrationSettings::GetCameraID()
	{
		return m_cameraID;
	}

	std::string CalibrationSettings::GetVideoFile()
	{
		return m_videoFile;
	}

	std::vector<std::string> CalibrationSettings::GetImageList()
	{
		return m_imageList;
	}

	int CalibrationSettings::GetBoardWidth()
	{
		return m_boardWidth;
	}

	void CalibrationSettings::SetBoardWidth(int p_boardWidth)
	{
		m_boardWidth = p_boardWidth;
	}

	int CalibrationSettings::GetBoardHeight()
	{
		return m_boardHeight;
	}

	void CalibrationSettings::SetBoardHeight(int p_boardHeight)
	{
		m_boardHeight = p_boardHeight;
	}

	cv::Size CalibrationSettings::GetBoardSize()
	{
		return cv::Size(m_boardWidth, m_boardHeight);
	}

	int CalibrationSettings::GetSquareSize()
	{
		return m_squareSize;
	}

	void CalibrationSettings::SetSquareSize(int p_squareSize)
	{
		m_squareSize = p_squareSize;
	}

	CalibrationSettings::Pattern CalibrationSettings::GetCalibrationPattern()
	{
		return m_calibrationPattern;
	}

	void CalibrationSettings::SetCalibrationPattern(CalibrationSettings::Pattern p_calibrationPattern)
	{
		m_calibrationPattern = p_calibrationPattern;
	}

	CalibrationSettings::InputType CalibrationSettings::GetInputType()
	{
		return m_inputType;
	}

	void CalibrationSettings::SetInputType(CalibrationSettings::InputType p_inputType)
	{
		m_inputType = p_inputType;
	}

	bool CalibrationSettings::GetInputFlipHorizontal()
	{
		return m_inputFlipHorizontal;
	}

	void CalibrationSettings::SetInputFlipHorizontal(bool p_inputFlipHorizontal)
	{
		m_inputFlipHorizontal = p_inputFlipHorizontal;
	}

	int CalibrationSettings::GetInputDelay()
	{
		return m_inputDelay;
	}

	void CalibrationSettings::SetInputDelay(int p_inputDelay)
	{
		m_inputDelay = p_inputDelay;
	}

	int CalibrationSettings::GetNumberOfFrames()
	{
		return m_numberOfFrames;
	}

	void CalibrationSettings::SetNumberOfFrames(int p_numberOfFrames)
	{
		m_numberOfFrames = p_numberOfFrames;
	}

	float CalibrationSettings::GetAspectRatio()
	{
		return m_aspactRatio;
	}

	void CalibrationSettings::SetAspectRatio(float p_aspectRatio)
	{
		m_aspactRatio = p_aspectRatio;
	}

	bool CalibrationSettings::GetAssumeZeroTangentialDistortion()
	{
		return m_assumeZeroTangentialDistortion;
	}

	void CalibrationSettings::SetAssumeZeroTangentialDistortion(bool p_assumeZeroTangentialDistortion)
	{
		m_assumeZeroTangentialDistortion = p_assumeZeroTangentialDistortion;
	}

	bool CalibrationSettings::GetAssumePrincipalPointCenter()
	{
		return m_assumePrincipalPointCenter;
	}

	void CalibrationSettings::SetAssumePrincipalPointCenter(bool p_assumePrincipalPointCenter)
	{
		m_assumePrincipalPointCenter = p_assumePrincipalPointCenter;
	}

	std::string CalibrationSettings::GetOutputFilename()
	{
		return m_outputFilename;
	}

	void CalibrationSettings::SetOutputFilename(std::string p_outputFilename)
	{
		m_outputFilename = p_outputFilename;
	}

	bool CalibrationSettings::GetOutputDetectFeaturePoints()
	{
		return m_outputDetectFeaturePoints;
	}

	void CalibrationSettings::SetOutputDetectFeaturePoints(bool p_outputDetectFeaturePoints)
	{
		m_outputDetectFeaturePoints = p_outputDetectFeaturePoints;
	}

	bool CalibrationSettings::GetOutputExtrinsicParameters()
	{
		return m_outputExtrinsicParameters;
	}

	void CalibrationSettings::SetOutputExtrinsicParameters(bool p_outputExtrinsicParameters)
	{
		m_outputExtrinsicParameters = p_outputExtrinsicParameters;
	}

	bool CalibrationSettings::GetShowUndistortedImage()
	{
		return m_showUndistortedImage;
	}

	void CalibrationSettings::SetShowUndistortedImage(bool p_showUndistortedImage)
	{
		m_showUndistortedImage = p_showUndistortedImage;
	}

	int CalibrationSettings::GetFlag()
	{
		return m_flag;
	}
}