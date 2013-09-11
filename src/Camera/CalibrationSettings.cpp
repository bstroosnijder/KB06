#include "Camera\CalibrationSettings.h"

namespace Camera
{

void CalibrationSettings::Write(cv::FileStorage& fs)   
	{
		fs << "{" << "BoardSize_Width"  << boardSize.width
			<< "BoardSize_Height" << boardSize.height
			<< "Square_Size"         << squareSize
			<< "Calibrate_Pattern" << patternToUse
			<< "Calibrate_NrOfFrameToUse" << nrFrames
			<< "Calibrate_FixAspectRatio" << aspectRatio
			<< "Calibrate_AssumeZeroTangentialDistortion" << calibZeroTangentDist
			<< "Calibrate_FixPrincipalPointAtTheCenter" << calibFixPrincipalPoint

			<< "Write_DetectedFeaturePoints" << bwritePoints
			<< "Write_extrinsicParameters"   << bwriteExtrinsics
			<< "Write_outputFileName"  << outputFileName

			<< "Show_UndistortedImage" << showUndistorsed

			<< "Input_FlipAroundHorizontalAxis" << flipVertical
			<< "Input_Delay" << delay
			<< "Input" << input
			<< "}";
	}

	void CalibrationSettings::Read(const cv::FileNode& node)                          //Read serialization for this class
	{
		node["BoardSize_Width" ] >> boardSize.width;
		node["BoardSize_Height"] >> boardSize.height;
		node["Calibrate_Pattern"] >> patternToUse;
		node["Square_Size"]  >> squareSize;
		node["Calibrate_NrOfFrameToUse"] >> nrFrames;
		node["Calibrate_FixAspectRatio"] >> aspectRatio;
		node["Write_DetectedFeaturePoints"] >> bwritePoints;
		node["Write_extrinsicParameters"] >> bwriteExtrinsics;
		node["Write_outputFileName"] >> outputFileName;
		node["Calibrate_AssumeZeroTangentialDistortion"] >> calibZeroTangentDist;
		node["Calibrate_FixPrincipalPointAtTheCenter"] >> calibFixPrincipalPoint;
		node["Input_FlipAroundHorizontalAxis"] >> flipVertical;
		node["Show_UndistortedImage"] >> showUndistorsed;
		node["Input"] >> input;
		node["Input_Delay"] >> delay;
		Interprate();
	}

	void CalibrationSettings::Interprate()
	{
		goodInput = true;
		if (boardSize.width <= 0 || boardSize.height <= 0)
		{
			std::cerr << "Invalid Board size: " << boardSize.width << " " << boardSize.height << std::endl;
			goodInput = false;
		}
		if (squareSize <= 10e-6)
		{
			std::cerr << "Invalid square size " << squareSize << std::endl;
			goodInput = false;
		}
		if (nrFrames <= 0)
		{
			std::cerr << "Invalid number of frames " << nrFrames << std::endl;
			goodInput = false;
		}

		if (input.empty())      // Check for valid input
			inputType = INVALID;
		else
		{
			if (input[0] >= '0' && input[0] <= '9')
			{
				std::stringstream ss(input);
				ss >> cameraID;
				inputType = CAMERA;
			}
			else
			{
				if (ReadStringList(input, imageList))
				{
					inputType = IMAGE_LIST;
					nrFrames = (nrFrames < (int)imageList.size()) ? nrFrames : (int)imageList.size();
				}
				else
					inputType = VIDEO_FILE;
			}
			if (inputType == CAMERA)
				inputCapture.open(cameraID);
			if (inputType == VIDEO_FILE)
				inputCapture.open(input);
			if (inputType != IMAGE_LIST && !inputCapture.isOpened())
				inputType = INVALID;
		}
		if (inputType == INVALID)
		{
			std::cerr << " Inexistent input: " << input;
			goodInput = false;
		}

		flag = 0;
		if(calibFixPrincipalPoint) flag |= CV_CALIB_FIX_PRINCIPAL_POINT;
		if(calibZeroTangentDist)   flag |= CV_CALIB_ZERO_TANGENT_DIST;
		if(aspectRatio)            flag |= CV_CALIB_FIX_ASPECT_RATIO;


		calibrationPattern = NOT_EXISTING;
		if (!patternToUse.compare("CHESSBOARD")) calibrationPattern = CHESSBOARD;
		if (!patternToUse.compare("CIRCLES_GRID")) calibrationPattern = CIRCLES_GRID;
		if (!patternToUse.compare("ASYMMETRIC_CIRCLES_GRID")) calibrationPattern = ASYMMETRIC_CIRCLES_GRID;
		if (calibrationPattern == NOT_EXISTING)
		{
			std::cerr << " Inexistent camera calibration mode: " << patternToUse << std::endl;
			goodInput = false;
		}
		atImageList = 0;
	}

	cv::Mat CalibrationSettings::NextImage()
	{
		cv::Mat result;
		if( inputCapture.isOpened() )
		{
			cv::Mat view0;
			inputCapture >> view0;
			view0.copyTo(result);
		}
		else if( atImageList < (int)imageList.size() )
			result = cv::imread(imageList[atImageList++], CV_LOAD_IMAGE_COLOR);

		return result;
	}

	bool CalibrationSettings::ReadStringList( const std::string& filename, std::vector<std::string>& l )
	{
		l.clear();
		cv::FileStorage fs(filename, cv::FileStorage::READ);
		if( !fs.isOpened() )
			return false;
		cv::FileNode n = fs.getFirstTopLevelNode();
		if( n.type() != cv::FileNode::SEQ )
			return false;
		cv::FileNodeIterator it = n.begin(), it_end = n.end();
		for( ; it != it_end; ++it )
			l.push_back((std::string)*it);
		return true;
	}

}
