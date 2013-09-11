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
		bool goodInput;

	
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
		
		int flag;
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
	};
}