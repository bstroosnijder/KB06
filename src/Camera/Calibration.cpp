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

	int Calibration::Start(int argc, char* argv[]){
		Help();
		CalibrationSettings s;
		//int argc = 0;
		const std::string inputSettingsFile = argc > 1 ? argv[1] : "IN_VID5.xml";
		cv::FileStorage fs(inputSettingsFile, cv::FileStorage::READ); // Read the settings
		if (!fs.isOpened())
		{
			std::cout << "Could not open the configuration file: \"" << inputSettingsFile << "\"" << std::endl;
			return -1;
		}
		//CalibrationSettings::goohdInput = (true);
		fs["Settings"] >> s.goodInput;
		fs.release();                                         // close Settings file

		if (!s.goodInput)
		{
			std::cout << "Invalid input detected. Application stopping. " << std::endl;
			system("pause");
			return -1;
		}

		std::vector<std::vector<cv::Point2f> > imagePoints;
		cv::Mat cameraMatrix, distCoeffs;
		cv::Size imageSize;
		int mode = s.inputType == CalibrationSettings::IMAGE_LIST ? CAPTURING : DETECTION;
		clock_t prevTimestamp = 0;
		const cv::Scalar RED(0,0,255), GREEN(0,255,0);
		const char ESC_KEY = 27;

		for(int i = 0;;++i)
		{
			cv::Mat view;
			bool blinkOutput = false;

			_sleep(1000);

			view = s.NextImage();

			//-----  If no more image, or got enough, then stop calibration and show result -------------
			if( mode == CAPTURING && imagePoints.size() >= (unsigned)s.nrFrames )
			{
				if( RunCalibrationAndSave(s, imageSize,  cameraMatrix, distCoeffs, imagePoints))
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
			if( s.flipVertical )    flip( view, view, 0 );

			std::vector<cv::Point2f> pointBuf;

			bool found;
			switch( s.calibrationPattern ) // Find feature points on the input format
			{
			case CalibrationSettings::CHESSBOARD:
				found = findChessboardCorners( view, s.boardSize, pointBuf,
					CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
				break;
			case CalibrationSettings::CIRCLES_GRID:
				found = findCirclesGrid( view, s.boardSize, pointBuf );
				break;
			case CalibrationSettings::ASYMMETRIC_CIRCLES_GRID:
				found = findCirclesGrid( view, s.boardSize, pointBuf, CALIB_CB_ASYMMETRIC_GRID );
				break;
			default:
				found = false;
				break;
			}

			if ( found)                // If done with success,
			{
				// improve the found corners' coordinate accuracy for chessboard
				if( s.calibrationPattern == CalibrationSettings::CHESSBOARD)
				{
					cv::Mat viewGray;
					cvtColor(view, viewGray, CV_BGR2GRAY);
					cornerSubPix( viewGray, pointBuf, cv::Size(11,11),
						cv::Size(-1,-1), cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
				}

				if( mode == CAPTURING &&  // For camera only take new samples after delay time
					(!s.inputCapture.isOpened() || clock() - prevTimestamp > s.delay*1e-3*CLOCKS_PER_SEC) )
				{
					imagePoints.push_back(pointBuf);
					prevTimestamp = clock();
					blinkOutput = s.inputCapture.isOpened();
				}

				// Draw the corners.
				drawChessboardCorners( view, s.boardSize, cv::Mat(pointBuf), found );
			}

			//----------------------------- Output Text ------------------------------------------------
			std::string msg = (mode == CAPTURING) ? "100/100" :
				mode == CALIBRATED ? "Calibrated" : "Press 'g' to start";
			int baseLine = 0;
			cv::Size textSize = cv::getTextSize(msg, 1, 1, 1, &baseLine);
			cv::Point textOrigin(view.cols - 2*textSize.width - 10, view.rows - 2*baseLine - 10);

			if( mode == CAPTURING )
			{
				if(s.showUndistorsed)
					msg = cv::format( "%d/%d Undist", (int)imagePoints.size(), s.nrFrames );
				else
					msg = cv::format( "%d/%d", (int)imagePoints.size(), s.nrFrames );
			}

			putText( view, msg, textOrigin, 1, 1, mode == CALIBRATED ?  GREEN : RED);

			if( blinkOutput )
				bitwise_not(view, view);

			//------------------------- Video capture  output  undistorted ------------------------------
			if( mode == CALIBRATED && s.showUndistorsed )
			{
				cv::Mat temp = view.clone();
				undistort(temp, view, cameraMatrix, distCoeffs);
			}

			//------------------------------ Show image and check for input commands -------------------
			imshow("Image View", view);
			char key = (char)cv::waitKey(s.inputCapture.isOpened() ? 50 : s.delay);

			if( key  == ESC_KEY )
				break;

			if( key == 'u' && mode == CALIBRATED )
				s.showUndistorsed = !s.showUndistorsed;

			if( s.inputCapture.isOpened() && key == 'g' )
			{
				mode = CAPTURING;
				imagePoints.clear();
			}
		}

		// -----------------------Show the undistorted image for the image list ------------------------
		if( s.inputType == CalibrationSettings::IMAGE_LIST && s.showUndistorsed )
		{
			cv::Mat view, rview, map1, map2;
			initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(),
				getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
				imageSize, CV_16SC2, map1, map2);

			for(int i = 0; i < (int)s.imageList.size(); i++ )
			{
				view = cv::imread(s.imageList[i], 1);
				if(view.empty())
					continue;
				remap(view, rview, map1, map2, INTER_LINEAR);
				imshow("Image View", rview);
				char c = (char)cv::waitKey();
				if( c  == ESC_KEY || c == 'q' || c == 'Q' )
					break;
			}
		}


		return 0;
	}

	double ComputeReprojectionErrors( const std::vector<std::vector<cv::Point3f> >& objectPoints,
			const std::vector<std::vector<cv::Point2f> >& imagePoints,
			const std::vector<cv::Mat>& rvecs, const std::vector<cv::Mat>& tvecs,
			const cv::Mat& cameraMatrix , const cv::Mat& distCoeffs,
			std::vector<float>& perViewErrors)
	{
		std::vector<cv::Point2f> imagePoints2;
		int i, totalPoints = 0;
		double totalErr = 0, err;
		perViewErrors.resize(objectPoints.size());

		for( i = 0; i < (int)objectPoints.size(); ++i )
		{
			projectPoints( cv::Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix,
				distCoeffs, imagePoints2);
			err = norm(cv::Mat(imagePoints[i]), cv::Mat(imagePoints2), CV_L2);

			int n = (int)objectPoints[i].size();
			perViewErrors[i] = (float) std::sqrt(err*err/n);
			totalErr        += err*err;
			totalPoints     += n;
		}

		return std::sqrt(totalErr/totalPoints);
	}

	void Calibration::CalcBoardCornerPositions(cv::Size boardSize, float squareSize, std::vector<cv::Point3f>& corners,
		CalibrationSettings::Pattern patternType /*= Settings::CHESSBOARD*/)
	{
		corners.clear();

		switch(patternType)
		{
		case CalibrationSettings::CHESSBOARD:
		case CalibrationSettings::CIRCLES_GRID:
			for( int i = 0; i < boardSize.height; ++i )
				for( int j = 0; j < boardSize.width; ++j )
					corners.push_back(cv::Point3f(float( j*squareSize ), float( i*squareSize ), 0));
			break;

		case CalibrationSettings::ASYMMETRIC_CIRCLES_GRID:
			for( int i = 0; i < boardSize.height; i++ )
				for( int j = 0; j < boardSize.width; j++ )
					corners.push_back(cv::Point3f(float((2*j + i % 2)*squareSize), float(i*squareSize), 0));
			break;
		default:
			break;
		}
	}

	void Calibration::SaveCameraParams( CalibrationSettings& s, cv::Size& imageSize, cv::Mat& cameraMatrix, cv::Mat& distCoeffs,
			const std::vector<cv::Mat>& rvecs, const std::vector<cv::Mat>& tvecs,
			const std::vector<float>& reprojErrs, const std::vector<std::vector<cv::Point2f> >& imagePoints,
			double totalAvgErr )
	{
		cv::FileStorage fs( s.outputFileName, cv::FileStorage::WRITE );

		time_t tm;
		time( &tm );
		struct tm *t2 = localtime( &tm );
		char buf[1024];
		strftime( buf, sizeof(buf)-1, "%c", t2 );

		fs << "calibration_Time" << buf;

		if( !rvecs.empty() || !reprojErrs.empty() )
			fs << "nrOfFrames" << (int)std::max(rvecs.size(), reprojErrs.size());
		fs << "image_Width" << imageSize.width;
		fs << "image_Height" << imageSize.height;
		fs << "board_Width" << s.boardSize.width;
		fs << "board_Height" << s.boardSize.height;
		fs << "square_Size" << s.squareSize;

		if( s.flag & CV_CALIB_FIX_ASPECT_RATIO )
			fs << "FixAspectRatio" << s.aspectRatio;

		if( s.flag )
		{
			sprintf( buf, "flags: %s%s%s%s",
				s.flag & CV_CALIB_USE_INTRINSIC_GUESS ? " +use_intrinsic_guess" : "",
				s.flag & CV_CALIB_FIX_ASPECT_RATIO ? " +fix_aspectRatio" : "",
				s.flag & CV_CALIB_FIX_PRINCIPAL_POINT ? " +fix_principal_point" : "",
				s.flag & CV_CALIB_ZERO_TANGENT_DIST ? " +zero_tangent_dist" : "" );
			cvWriteComment( *fs, buf, 0 );

		}

		fs << "flagValue" << s.flag;

		fs << "Camera_Matrix" << cameraMatrix;
		fs << "Distortion_Coefficients" << distCoeffs;

		fs << "Avg_Reprojection_Error" << totalAvgErr;
		if( !reprojErrs.empty() )
			fs << "Per_View_Reprojection_Errors" << cv::Mat(reprojErrs);

		if( !rvecs.empty() && !tvecs.empty() )
		{
			CV_Assert(rvecs[0].type() == tvecs[0].type());
			cv::Mat bigmat((int)rvecs.size(), 6, rvecs[0].type());
			for( int i = 0; i < (int)rvecs.size(); i++ )
			{
				cv::Mat r = bigmat(cv::Range(i, i+1), cv::Range(0,3));
				cv::Mat t = bigmat(cv::Range(i, i+1), cv::Range(3,6));

				CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
				CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
				//*.t() is MatExpr (not Mat) so we can use assignment operator
				r = rvecs[i].t();
				t = tvecs[i].t();
			}
			cvWriteComment( *fs, "a set of 6-tuples (rotation vector + translation vector) for each view", 0 );
			fs << "Extrinsic_Parameters" << bigmat;
		}

		if( !imagePoints.empty() )
		{
			cv::Mat imagePtMat((int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
			for( int i = 0; i < (int)imagePoints.size(); i++ )
			{
				cv::Mat r = imagePtMat.row(i).reshape(2, imagePtMat.cols);
				cv::Mat imgpti(imagePoints[i]);
				imgpti.copyTo(r);
			}
			fs << "Image_points" << imagePtMat;
		}
	}

	bool Calibration::RunCalibrationAndSave(CalibrationSettings& s, cv::Size imageSize, cv::Mat&  cameraMatrix, cv::Mat& distCoeffs,std::vector<std::vector<cv::Point2f> > imagePoints )
	{
		std::vector<cv::Mat> rvecs, tvecs;
		std::vector<float> reprojErrs;
		double totalAvgErr = 0;

		bool ok = RunCalibration(s,imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs,
			reprojErrs, totalAvgErr);
		std::cout << (ok ? "Calibration succeeded" : "Calibration failed")
			<< ". avg re projection error = "  << totalAvgErr ;

		if( ok )
			SaveCameraParams( s, imageSize, cameraMatrix, distCoeffs, rvecs ,tvecs, reprojErrs,
			imagePoints, totalAvgErr);
		return ok;
	}

	bool Calibration::RunCalibration( CalibrationSettings& s, cv::Size& imageSize, cv::Mat& cameraMatrix, cv::Mat& distCoeffs,
			std::vector<std::vector<cv::Point2f> > imagePoints, std::vector<cv::Mat>& rvecs, std::vector<cv::Mat>& tvecs,
			std::vector<float>& reprojErrs,  double& totalAvgErr)
	{
	
	    cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
	    if( s.flag & CV_CALIB_FIX_ASPECT_RATIO )
	        cameraMatrix.at<double>(0,0) = 1.0;
	
	    distCoeffs = cv::Mat::zeros(8, 1, CV_64F);
	
	    std::vector<std::vector<cv::Point3f> > objectPoints(1);
	    CalcBoardCornerPositions(s.boardSize, s.squareSize, objectPoints[0], s.calibrationPattern);
	
	    objectPoints.resize(imagePoints.size(),objectPoints[0]);
	
	    //Find intrinsic and extrinsic camera parameters
	    double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
	                                 distCoeffs, rvecs, tvecs, s.flag|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);
	
	    std::cout << "Re-projection error reported by calibrateCamera: "<< rms << std::endl;
	
	    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);
	
		//reprojerrs wss de fout
		//std::vector<float> naam; 
	    //totalAvgErr = Calibration::ComputeReprojectionErrors(objectPoints, imagePoints,
	    //                                         rvecs, tvecs, cameraMatrix, distCoeffs, naam);
	
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