#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace Camera
{
class CalibrationSettings
	{
	public:
		enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
		enum InputType {INVALID, CAMERA, VIDEO_FILE, IMAGE_LIST};
		bool m_goodInput;

	
		std::string m_patternToUse;
		cv::Size m_boardSize;            // The size of the board -> Number of items by width and height
		Pattern m_calibrationPattern;// One of the Chessboard, circles, or asymmetric circle pattern
		float m_squareSize;          // The size of a square in your defined unit (point, millimeter,etc).
		int m_nrFrames;              // The number of frames to use from the input for calibration
		float m_aspectRatio;         // The aspect ratio
		int m_delay;                 // In case of a video input
		bool m_bwritePoints;         //  Write detected feature points
		bool m_bwriteExtrinsics;     // Write extrinsic parameters
		bool m_calibZeroTangentDist; // Assume zero tangential distortion
		bool m_calibFixPrincipalPoint;// Fix the principal point at the center
		bool m_flipVertical;          // Flip the captured images around the horizontal axis
		std::string m_outputFileName;      // The name of the file where to write
		bool m_showUndistorsed;       // Show undistorted images after calibration
		std::string m_input;               // The input ->
		int m_cameraID;
		std::vector<std::string> m_imageList;
		int m_atImageList;
		cv::VideoCapture m_inputCapture;
		InputType m_inputType;
		int m_flag;

       /**
		* @brief	Comment TODO, Function complete
		*/
		void Write(cv::FileStorage& p_fs);

	   /**
		* @brief	Comment TODO, Function complete
		*/
		void Read(const cv::FileNode& P_NODE);

	   /**
		* @brief	Comment TODO, Function complete
		*/
		void Interprate();

	   /**
		* @brief	Comment TODO, Function complete
		*/
		cv::Mat NextImage();

	   /**
		* @brief	Comment TODO, Function complete
		*/
		bool ReadStringList( const std::string& P_FILENAME, std::vector<std::string>& p_l );
	};
}