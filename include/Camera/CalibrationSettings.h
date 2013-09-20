#ifndef __CAMERA__CALIBRATIONSETTINGS__H__
#define __CAMERA__CALIBRATIONSETTINGS__H__

#include <opencv/cv.h>
#include <string>
#include <sstream>
#include <vector>


namespace Camera
{
	/**
	 * @brief	TODO
	 * @author	Alex Hodes
	 */
	class CalibrationSettings
	{
	public:
		// TODO
		bool m_goodInput;

		/*
		 * @brief	TODO
		 * @author	Alex Hodes
		 */
		enum Pattern
		{
			NOT_EXISTING,
			CHESSBOARD,
			CIRCLES_GRID,
			ASYMMETRIC_CIRCLES_GRID
		};

		/*
		 * @brief	TODO
		 * @author	Alex Hodes
		 */
		enum InputType
		{
			INVALID,
			CAMERA,
			VIDEO_FILE,
			IMAGE_LIST
		};

		/**
		 * @brief	Constructor
		 * @param	p_filename The name of the file to load and to save to
		 */
		CalibrationSettings(std::string p_filename);

		/**
		 * @brief	Deconstructor
		 */
		~CalibrationSettings();

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();

		/**
		 * @brief	Save data to file
		 */
		void Save();

		/**
		 * @brief	Checks whether the file is opened and the input is good
		 * @return	Whether the file is opened and the input is good
		 */
		bool GetIsOpenedAndGood();

		/**
		 * @brief	Gets the camera ID
		 * @return	The camera ID
		 */
		int GetCameraID();

		/**
		 * @brief	Gets the video file
		 * @return	The video file
		 */
		std::string GetVideoFile();

		/**
		 * @brief	Gets the image list
		 * @return	The image list
		 */
		std::vector<std::string> GetImageList();

		/*
		 * @brief	Gets the board width
		 * @return	The board width
		 */
		int GetBoardWidth();

		/**
		 * @brief	Sets the board width
		 * @param	p_boardWidth The board width
		 */
		void SetBoardWidth(int p_boardWidth);

		/*
		 * @brief	Gets the board height
		 * @return	The board height
		 */
		int GetBoardHeight();

		/**
		 * @brief	Sets the board height
		 * @param	p_boardHeight The board height
		 */
		void SetBoardHeight(int p_boardHeight);

		/**
		 * @brief	Gets the size of the board
		 * @return	The size of the board
		 */
		cv::Size GetBoardSize();

		/*
		 * @brief	Gets the square size
		 * @return	The board square size
		 */
		int GetSquareSize();

		/**
		 * @brief	Sets the square size
		 * @param	p_squareSize The square size
		 */
		void SetSquareSize(int p_squareSize);

		/*
		 * @brief	Gets the calibration pattern
		 * @return	The calibration pattern
		 */
		Pattern GetCalibrationPattern();

		/**
		 * @brief	Sets the calibration pattern
		 * @param	p_calibrationPattern The calibration pattern
		 */
		void SetCalibrationPattern(Pattern p_calibrationPattern);

		/*
		 * @brief	Gets the input type
		 * @return	The input type
		 */
		InputType GetInputType();

		/**
		 * @brief	Sets the input type
		 * @param	p_inputType The input type
		 */
		void SetInputType(InputType p_inputType);

		/*
		 * @brief	Gets the input flip horizontal
		 * @return	The input flip horizontal
		 */
		bool GetInputFlipHorizontal();

		/**
		 * @brief	Sets the input flip horizontal
		 * @param	p_inputFlipHorizontal The input flip horizontal
		 */
		void SetInputFlipHorizontal(bool p_inputFlipHorizontal);

		/*
		 * @brief	Gets the input delay
		 * @return	The input delay
		 */
		int GetInputDelay();

		/**
		 * @brief	Sets the input delay
		 * @param	p_inputDelay The input delay
		 */
		void SetInputDelay(int p_inputDelay);

		/*
		 * @brief	Gets the number of frames
		 * @return	The number of frames
		 */
		int GetNumberOfFrames();

		/**
		 * @brief	Sets the number of frames
		 * @param	p_numberOfFrames The number of frames
		 */
		void SetNumberOfFrames(int p_numberOfFrames);

		/*
		 * @brief	Gets the aspect ratio
		 * @return	The aspect ratio
		 */
		float GetAspectRatio();

		/**
		 * @brief	Sets the aspect ratio
		 * @param	p_aspectRatio The aspect ratio
		 */
		void SetAspectRatio(float p_aspectRatio);

		/*
		 * @brief	Gets the assume zero tangential distortion
		 * @return	The assume zero tangential distortion
		 */
		bool GetAssumeZeroTangentialDistortion();

		/**
		 * @brief	Sets the assume zero tangential distortion
		 * @param	p_assumeZeroTangentialDistortion The assume zero tangential distortion
		 */
		void SetAssumeZeroTangentialDistortion(bool p_assumeZeroTangentialDistortion);

		/*
		 * @brief	Gets the assume principal point center
		 * @return	The assume principal point center
		 */
		bool GetAssumePrincipalPointCenter();

		/**
		 * @brief	Sets the assume principal point center
		 * @param	p_assumePrincipalPointCenter The assume principal point center
		 */
		void SetAssumePrincipalPointCenter(bool p_assumePrincipalPointCenter);

		/*
		 * @brief	Gets the output filename
		 * @return	The output filename
		 */
		std::string GetOutputFilename();

		/**
		 * @brief	Sets the output filename
		 * @param	p_outputFilename The output filename
		 */
		void SetOutputFilename(std::string p_outputFilename);

		/*
		 * @brief	Gets the output detect feature points
		 * @return	The output detect feature points
		 */
		bool GetOutputDetectFeaturePoints();

		/**
		 * @brief	Sets the output detect feature points
		 * @param	p_outputDetectFeaturePoints The output detect feature points
		 */
		void SetOutputDetectFeaturePoints(bool p_outputDetectFeaturePoints);

		/*
		 * @brief	Gets the output extrinsic parameters
		 * @return	The output extrinsic parameters
		 */
		bool GetOutputExtrinsicParameters();

		/**
		 * @brief	Sets the output extrinsic parameters
		 * @param	p_outputExtrinsicParameters The output extrinsic parameters
		 */
		void SetOutputExtrinsicParameters(bool p_outputExtrinsicParameters);

		/*
		 * @brief	Gets the show undistorted image
		 * @return	The show undistorted image
		 */
		bool GetShowUndistortedImage();

		/**
		 * @brief	Sets the show undistorted image
		 * @param	p_showUndistortedImage The show undistorted image
		 */
		void SetShowUndistortedImage(bool p_showUndistortedImage);

		/**
		 * @brief	Gets the flag
		 * @return	The flag
		 */
		int GetFlag();

	private:
		std::string m_filename;
		bool m_isOpenedAndGood;
		int m_cameraID;
		std::string m_videoFile;
		std::vector<std::string> m_imageList;
		int m_boardWidth;
		int m_boardHeight;
		int m_squareSize;
		Pattern m_calibrationPattern;
		InputType m_inputType;
		bool m_inputFlipHorizontal;
		int m_inputDelay;
		int m_numberOfFrames;
		float m_aspactRatio;
		bool m_assumeZeroTangentialDistortion;
		bool m_assumePrincipalPointCenter;
		std::string m_outputFilename;
		bool m_outputDetectFeaturePoints;
		bool m_outputExtrinsicParameters;
		bool m_showUndistortedImage;
		int m_flag;

		/**
		* @brief	Check if the given file contains an image list
		* @param	p_filename The filename to read and check
		* @return	Whether or not it's a image list
		*/
		bool IsImageList(std::string p_filename);
	};
}

#endif