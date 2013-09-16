#include "Camera/Calibration.h"

namespace Camera
{

	Calibration::Calibration()
	{
		//niet conventie
		//this->goodInput = false;
		//enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };
		//enum InputType {INVALID, CAMERA, VIDEO_FILE, IMAGE_LIST};
	}

	int Calibration::Start(int p_argc, char* p_argv[]){
		Help();
		CalibrationSettings s;
		//int argc = 0;
		const std::string inputSettingsFile = p_argc > 1 ? p_argv[1] : "IN_VID5.xml";
		cv::FileStorage fs(inputSettingsFile, cv::FileStorage::READ); // Read the settings
		if (!fs.isOpened())
		{
			std::cout << "Could not open the configuration file: \"" << inputSettingsFile << "\"" << std::endl;
			return -1;
		}

		s.Read(fs["Settings"]);
		fs.release();                                         // close Settings file

		if (!s.m_goodInput)
		{
			std::cout << "Invalid input detected. Application stopping. " << std::endl;
			system("pause");
			return -1;
		}

		std::vector<std::vector<cv::Point2f> > imagePoints;
		cv::Mat cameraMatrix, distCoeffs;
		cv::Size imageSize;
		int mode = s.m_inputType == CalibrationSettings::IMAGE_LIST ? CAPTURING : DETECTION;
		clock_t prevTimestamp = 0;
		const cv::Scalar RED(0,0,255), GREEN(0,255,0);
		const char ESC_KEY = 27;
		_sleep(500);
		for(int i = 0;;++i)
		{
			cv::Mat view;
			bool blinkOutput = false;

			//_sleep(3);
			//cv::waitKey();
			view = s.NextImage();

			//-----  If no more image, or got enough, then stop calibration and show result -------------
			if(mode == CAPTURING && imagePoints.size() >= (unsigned)s.m_nrFrames)
			{
				if( RunCalibrationAndSave(s, imageSize, cameraMatrix, distCoeffs, imagePoints))
					mode = CALIBRATED;
				else
					mode = DETECTION;
			}
			if(view.empty())          // If no more images then run calibration, save and stop loop.
			{
				if( imagePoints.size() > 0 )
					RunCalibrationAndSave(s, imageSize,  cameraMatrix, distCoeffs, imagePoints);
				break;
			}


			imageSize = view.size();  // Format input image.
			if(s.m_flipVertical)    flip(view, view, 0);

			std::vector<cv::Point2f> pointBuf;

			bool found;
			switch(s.m_calibrationPattern) // Find feature points on the input format
			{
			case CalibrationSettings::CHESSBOARD:
				found = findChessboardCorners(view, s.m_boardSize, pointBuf,
					CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
				break;
			case CalibrationSettings::CIRCLES_GRID:
				found = findCirclesGrid(view, s.m_boardSize, pointBuf );
				break;
			case CalibrationSettings::ASYMMETRIC_CIRCLES_GRID:
				found = findCirclesGrid(view, s.m_boardSize, pointBuf, CALIB_CB_ASYMMETRIC_GRID );
				break;
			default:
				found = false;
				break;
			}

			if (found)                // If done with success,
			{
				
				// improve the found corners' coordinate accuracy for chessboard
				if(s.m_calibrationPattern == CalibrationSettings::CHESSBOARD)
				{
					cv::Mat viewGray;
					cvtColor(view, viewGray, CV_BGR2GRAY);
					cornerSubPix(viewGray, pointBuf, cv::Size(11, 11),
						cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1));
				}

				if(mode == CAPTURING &&  // For camera only take new samples after delay time
					(!s.m_inputCapture.isOpened() || clock() - prevTimestamp > s.m_delay*1e-3*CLOCKS_PER_SEC) )
				{
						imagePoints.push_back(pointBuf);
						prevTimestamp = clock();
						blinkOutput = s.m_inputCapture.isOpened();	
				}

				// Draw the corners.
				drawChessboardCorners(view, s.m_boardSize, cv::Mat(pointBuf), found);
			}

			//----------------------------- Output Text ------------------------------------------------
			std::string msg = (mode == CAPTURING) ? "100/100" :
				mode == CALIBRATED ? "Calibrated" : "Press 'g' to start";
			int baseLine = 0;
			cv::Size textSize = cv::getTextSize(msg, 1, 1, 1, &baseLine);
			cv::Point textOrigin(view.cols - 2*textSize.width - 10, view.rows - 2*baseLine - 10);

			if(mode == CAPTURING)
			{
				if(s.m_showUndistorsed)
					msg = cv::format("%d/%d Undist", (int)imagePoints.size(), s.m_nrFrames);
				else
					msg = cv::format("%d/%d", (int)imagePoints.size(), s.m_nrFrames);
			}

			putText(view, msg, textOrigin, 1, 1, mode == CALIBRATED ? GREEN : RED);

			if(blinkOutput)
				bitwise_not(view, view);

			//------------------------- Video capture  output  undistorted ------------------------------
			if(mode == CALIBRATED && s.m_showUndistorsed)
			{
				cv::Mat temp = view.clone();
				undistort(temp, view, cameraMatrix, distCoeffs);
			}

			//------------------------------ Show image and check for input commands -------------------
			imshow("Image View", view);
			char key = (char)cv::waitKey(s.m_inputCapture.isOpened() ? 50 : s.m_delay);

			if(key  == ESC_KEY)
				break;

			if(key == 'u' && mode == CALIBRATED)
				s.m_showUndistorsed = !s.m_showUndistorsed;

			if(s.m_inputCapture.isOpened() && key == 'g')
			{
				mode = CAPTURING;
				imagePoints.clear();
			}
		}

		// -----------------------Show the undistorted image for the image list ------------------------
		if(s.m_inputType == CalibrationSettings::IMAGE_LIST && s.m_showUndistorsed)
		{
			cv::Mat view, rview, map1, map2;
			initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(),
				getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
				imageSize, CV_16SC2, map1, map2);

			for(int i = 0; i < (int)s.m_imageList.size(); i++)
			{
				view = cv::imread(s.m_imageList[i], 1);
				if(view.empty())
					continue;
				remap(view, rview, map1, map2, INTER_LINEAR);
				imshow("Image View", rview);
				char c = (char)cv::waitKey();
				if(c == ESC_KEY || c == 'q' || c == 'Q')
					break;
			}
		}


		return 0;
	}

	double Calibration::ComputeReprojectionErrors(const std::vector<std::vector<cv::Point3f> >& p_objectPoints,
			const std::vector<std::vector<cv::Point2f> >& p_imagePoints,
			const std::vector<cv::Mat>& p_rvecs, const std::vector<cv::Mat>& p_tvecs,
			const cv::Mat& p_cameraMatrix , const cv::Mat& p_distCoeffs,
			std::vector<float>& p_perViewErrors)
	{
		std::vector<cv::Point2f> imagePoints2;
		int i, totalPoints = 0;
		double totalErr = 0, err;
		p_perViewErrors.resize(p_objectPoints.size());

		for(i = 0; i < (int)p_objectPoints.size(); ++i)
		{
			projectPoints(cv::Mat(p_objectPoints[i]), p_rvecs[i], p_tvecs[i], p_cameraMatrix,
				p_distCoeffs, imagePoints2);
			err = norm(cv::Mat(p_imagePoints[i]), cv::Mat(imagePoints2), CV_L2);

			int n = (int)p_objectPoints[i].size();
			p_perViewErrors[i] = (float) std::sqrt(err*err/n);
			totalErr        += err*err;
			totalPoints     += n;
		}

		return std::sqrt(totalErr/totalPoints);
	}

	void Calibration::CalcBoardCornerPositions(cv::Size p_boardSize, float p_squareSize, std::vector<cv::Point3f>& p_corners,
			CalibrationSettings::Pattern p_patternType /*= Settings::CHESSBOARD*/)
	{
		p_corners.clear();

		switch(p_patternType)
		{
		case CalibrationSettings::CHESSBOARD:
		case CalibrationSettings::CIRCLES_GRID:
			for( int i = 0; i < p_boardSize.height; ++i )
				for( int j = 0; j < p_boardSize.width; ++j )
					p_corners.push_back(cv::Point3f(float( j*p_squareSize ), float( i*p_squareSize ), 0));
			break;

		case CalibrationSettings::ASYMMETRIC_CIRCLES_GRID:
			for( int i = 0; i < p_boardSize.height; i++ )
				for( int j = 0; j < p_boardSize.width; j++ )
					p_corners.push_back(cv::Point3f(float((2*j + i % 2)*p_squareSize), float(i*p_squareSize), 0));
			break;
		default:
			break;
		}
	}

	void Calibration::SaveCameraParams(CalibrationSettings& p_s, cv::Size& p_imageSize, cv::Mat& p_cameraMatrix, cv::Mat& p_distCoeffs,
			const std::vector<cv::Mat>& p_rvecs, const std::vector<cv::Mat>& p_tvecs,
			const std::vector<float>& p_reprojErrs, const std::vector<std::vector<cv::Point2f> >& p_imagePoints,
			double p_totalAvgErr )
	{
		cv::FileStorage fs( p_s.m_outputFileName, cv::FileStorage::WRITE );

		time_t tm;
		time( &tm );
		struct tm *t2 = localtime( &tm );
		char buf[1024];
		strftime( buf, sizeof(buf)-1, "%c", t2 );

		fs << "calibration_Time" << buf;

		if( !p_rvecs.empty() || !p_reprojErrs.empty() )
			fs << "nrOfFrames" << (int)std::max(p_rvecs.size(), p_reprojErrs.size());
		fs << "image_Width" << p_imageSize.width;
		fs << "image_Height" << p_imageSize.height;
		fs << "board_Width" << p_s.m_boardSize.width;
		fs << "board_Height" << p_s.m_boardSize.height;
		fs << "square_Size" << p_s.m_squareSize;

		if( p_s.m_flag & CV_CALIB_FIX_ASPECT_RATIO )
			fs << "FixAspectRatio" << p_s.m_aspectRatio;

		if( p_s.m_flag )
		{
			sprintf( buf, "flags: %s%s%s%s",
				p_s.m_flag & CV_CALIB_USE_INTRINSIC_GUESS ? " +use_intrinsic_guess" : "",
				p_s.m_flag & CV_CALIB_FIX_ASPECT_RATIO ? " +fix_aspectRatio" : "",
				p_s.m_flag & CV_CALIB_FIX_PRINCIPAL_POINT ? " +fix_principal_point" : "",
				p_s.m_flag & CV_CALIB_ZERO_TANGENT_DIST ? " +zero_tangent_dist" : "" );
			cvWriteComment( *fs, buf, 0 );

		}

		fs << "flagValue" << p_s.m_flag;

		fs << "Camera_Matrix" << p_cameraMatrix;
		fs << "Distortion_Coefficients" << p_distCoeffs;

		fs << "Avg_Reprojection_Error" << p_totalAvgErr;
		if( !p_reprojErrs.empty() )
			fs << "Per_View_Reprojection_Errors" << cv::Mat(p_reprojErrs);

		if( !p_rvecs.empty() && !p_tvecs.empty() )
		{
			CV_Assert(p_rvecs[0].type() == p_tvecs[0].type());
			cv::Mat bigmat((int)p_rvecs.size(), 6, p_rvecs[0].type());
			for( int i = 0; i < (int)p_rvecs.size(); i++ )
			{
				cv::Mat r = bigmat(cv::Range(i, i+1), cv::Range(0,3));
				cv::Mat t = bigmat(cv::Range(i, i+1), cv::Range(3,6));

				CV_Assert(p_rvecs[i].rows == 3 && p_rvecs[i].cols == 1);
				CV_Assert(p_tvecs[i].rows == 3 && p_tvecs[i].cols == 1);
				//*.t() is MatExpr (not Mat) so we can use assignment operator
				r = p_rvecs[i].t();
				t = p_tvecs[i].t();
			}
			cvWriteComment( *fs, "a set of 6-tuples (rotation vector + translation vector) for each view", 0 );
			fs << "Extrinsic_Parameters" << bigmat;
		}

		if( !p_imagePoints.empty() )
		{
			cv::Mat imagePtMat((int)p_imagePoints.size(), (int)p_imagePoints[0].size(), CV_32FC2);
			for( int i = 0; i < (int)p_imagePoints.size(); i++ )
			{
				cv::Mat r = imagePtMat.row(i).reshape(2, imagePtMat.cols);
				cv::Mat imgpti(p_imagePoints[i]);
				imgpti.copyTo(r);
			}
			fs << "Image_points" << imagePtMat;
		}
	}

	bool Calibration::RunCalibrationAndSave(CalibrationSettings& p_s, cv::Size p_imageSize, cv::Mat&  p_cameraMatrix, cv::Mat& p_distCoeffs,std::vector<std::vector<cv::Point2f> > p_imagePoints)
	{
		std::vector<cv::Mat> rvecs, tvecs;
		std::vector<float> reprojErrs;
		double totalAvgErr = 0;

		bool ok = RunCalibration(p_s,p_imageSize, p_cameraMatrix, p_distCoeffs, p_imagePoints, rvecs, tvecs,
			reprojErrs, totalAvgErr);
		std::cout << (ok ? "Calibration succeeded" : "Calibration failed")
			<< ". avg re projection error = "  << totalAvgErr ;

		if( ok )
			SaveCameraParams( p_s, p_imageSize, p_cameraMatrix, p_distCoeffs, rvecs ,tvecs, reprojErrs,
			p_imagePoints, totalAvgErr);
		return ok;
	}

	bool Calibration::RunCalibration(CalibrationSettings& p_s, cv::Size& p_imageSize, cv::Mat& p_cameraMatrix, cv::Mat& p_distCoeffs,
			std::vector<std::vector<cv::Point2f> > p_imagePoints, std::vector<cv::Mat>& p_rvecs, std::vector<cv::Mat>& p_tvecs,
			std::vector<float>& p_reprojErrs, double& p_totalAvgErr)
	{
	
	    p_cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
	    if( p_s.m_flag & CV_CALIB_FIX_ASPECT_RATIO )
	        p_cameraMatrix.at<double>(0,0) = 1.0;
	
	    p_distCoeffs = cv::Mat::zeros(8, 1, CV_64F);
	
	    std::vector<std::vector<cv::Point3f> > objectPoints(1);
	    CalcBoardCornerPositions(p_s.m_boardSize, p_s.m_squareSize, objectPoints[0], p_s.m_calibrationPattern);
	
	    objectPoints.resize(p_imagePoints.size(),objectPoints[0]);
	
	    //Find intrinsic and extrinsic camera parameters
	    double rms = calibrateCamera(objectPoints, p_imagePoints, p_imageSize, p_cameraMatrix,
	                                 p_distCoeffs, p_rvecs, p_tvecs, p_s.m_flag|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);
	
	    std::cout << "Re-projection error reported by calibrateCamera: "<< rms << std::endl;
	
	    bool ok = checkRange(p_cameraMatrix) && checkRange(p_distCoeffs);
	
		//reprojerrs wss de fout
		//std::vector<float> naam; 
	    p_totalAvgErr = Calibration::ComputeReprojectionErrors(objectPoints, p_imagePoints,
	                                             p_rvecs, p_tvecs, p_cameraMatrix, p_distCoeffs, p_reprojErrs);
	   


	    return ok;
	}

	void Calibration::Help()
	{
	    std::cout <<  "Welcome to the camera calibration!." << std::endl <<  
				"Usage: calibration configurationFile"  << std::endl <<
				"Near the sample file you'll find the configuration file, which has detailed help of "
	            "how to edit it.  It may be any OpenCV supported file format XML/YAML." << std::endl <<
				"Please hold an odd checkerboard in front of the camera!" << std::endl ;
	}

}