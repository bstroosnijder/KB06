#include "Camera/Calibration.h"

namespace Camera
{
	Calibration::Calibration()
	{
		m_settings = new CalibrationSettings("resources/camera_calibration_in.xml");
		m_params = new CalibrationParams(m_settings->GetOutputFilename());
		m_currentFrame = 0;

		switch (m_settings->GetInputType())
		{
		case CalibrationSettings::InputType::CAMERA:
			m_capture = cv::VideoCapture(m_settings->GetCameraID());
			break;

		case CalibrationSettings::InputType::VIDEO_FILE:
			m_capture = cv::VideoCapture(m_settings->GetVideoFile());
			break;
		}
	}

	Calibration::~Calibration()
	{
		Cleanup();
	}

	void Calibration::Cleanup()
	{
		cv::destroyAllWindows();
		m_capture.release();
		delete m_params;
		delete m_settings;
	}

	void Calibration::Start()
	{
		// Return empty if this isn't open
		if (!m_settings->GetIsOpenedAndGood())
		{
			return;
		}

		const char KEY_ESC = 27;
		const char KEY_U = 'u';
		const char KEY_G = 'g';

		State mode = m_settings->GetInputType() == CalibrationSettings::InputType::IMAGE_LIST
			? State::CAPTURING
			: State::DETECTION;

		cv::Size imageSize;
		cv::Mat cameraMatrix;
		cv::Mat distortionCoefficients;
		Contours contours;

		char key;
		bool isRunning = true;
		clock_t timestamp = 0;
		while (isRunning)
		{
			cv::Mat image;
			FetchNextImage(image);
			if (!image.empty())
			{
				bool blinkOutput = false;
				imageSize = image.size();
				if (m_settings->GetInputFlipHorizontal())
				{
					cv::flip(image, image, 0);
				}

				if (mode == State::CAPTURING &&
					contours.size() >= static_cast<unsigned int>(m_settings->GetNumberOfFrames()))
				{
					if (RunAndSaveCalibration(imageSize, cameraMatrix, distortionCoefficients, contours))
					{
						mode = State::CALIBRATED;
					}
					else
					{
						mode = State::DETECTION;
					}
				}

				bool found = false;
				Corners corners;
				switch (m_settings->GetCalibrationPattern())
				{
				case CalibrationSettings::Pattern::CHESSBOARD:
					found = cv::findChessboardCorners(image,
						m_settings->GetBoardSize(),
						corners,
						(CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE));
					break;

				case CalibrationSettings::Pattern::CIRCLES_GRID:
					found = cv::findCirclesGrid(image,
						m_settings->GetBoardSize(),
						corners);
					break;

				case CalibrationSettings::Pattern::ASYMMETRIC_CIRCLES_GRID:
					found = cv::findCirclesGrid(image,
						m_settings->GetBoardSize(),
						corners,
						CALIB_CB_ASYMMETRIC_GRID);
					break;
				}

				if (found)
				{
					// improve the found corners' coordinate accuracy for chessboard
					if (m_settings->GetCalibrationPattern() == CalibrationSettings::Pattern::CHESSBOARD)
					{
						cv::Mat gray;
						cv::cvtColor(image, gray, CV_BGR2GRAY);
						cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1),
							cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
					}

					// For camera only take new samples after delay time
					if (mode == State::CAPTURING &&
						((clock() - timestamp) > (m_settings->GetInputDelay() * 1e-3 * CLOCKS_PER_SEC)))
					{
						contours.push_back(corners);
						blinkOutput = m_capture.isOpened();
						// Up the current frame
						m_currentFrame++;
					}

					// Draw the corners.
					cv::drawChessboardCorners(image, m_settings->GetBoardSize(),
						cv::Mat(corners), found);
				}

				// Check if we need to blink output
				if (blinkOutput)
				{
					cv::bitwise_not(image, image);
				}

				// Check if we can undistort output
				if (mode == State::CALIBRATED && m_settings->GetShowUndistortedImage())
				{
					cv::undistort(image.clone(), image,
						cameraMatrix,
						distortionCoefficients);
				}

				// Show image
				cv::imshow("TEST", image);
				// Delay + capture key
				key = static_cast<char>(cv::waitKey(m_capture.isOpened()
					? 50
					: m_settings->GetInputDelay()));

				// Check for esc key
				if (key == KEY_ESC)
				{
					isRunning = false;
				}
				// Check for u key
				else if (key == KEY_U)
				{
					m_settings->SetShowUndistortedImage(!m_settings->GetShowUndistortedImage());
				}
				// Check for k key
				else if (key == KEY_G && m_capture.isOpened())
				{
					mode = State::CAPTURING;
					contours.clear();
				}
			}
			else
			{
				if (contours.size() > 0)
				{
					RunAndSaveCalibration(imageSize, cameraMatrix, distortionCoefficients, contours);
					isRunning = false;
				}
			}
		}
	}

	void Calibration::FetchNextImage(cv::Mat& p_image)
	{
		if (m_capture.isOpened())
		{
			m_capture >> p_image;
		}
		else
		{
			if (m_currentFrame <= m_settings->GetImageList().size())
			{
				p_image = cv::imread(m_settings->GetImageList().at(m_currentFrame), cv::IMREAD_COLOR);
				// Up the current frame
				m_currentFrame++;
			}
		}
	}

	bool Calibration::RunAndSaveCalibration(cv::Size& p_imageSize, cv::Mat& p_cameraMatrix,
		cv::Mat& p_distortionCoefficients, Contours& p_contours)
	{
		double averageReprojectionError = 0.0;
		PerViewErrors perViewReprojectionErrors;
		CvMats rvecs;
		CvMats tvecs;

		bool status = RunCalibration(p_imageSize, p_cameraMatrix,
			p_distortionCoefficients, p_contours,
			averageReprojectionError, perViewReprojectionErrors,
			rvecs, tvecs);
		if (status)
		{
			SaveParams(p_imageSize, p_cameraMatrix,
				p_distortionCoefficients, p_contours,
				averageReprojectionError, perViewReprojectionErrors,
				rvecs, tvecs);
		}

		return status;
	}

	bool Calibration::RunCalibration(cv::Size& p_imageSize, cv::Mat& p_cameraMatrix,
		cv::Mat& p_distortionCoefficients, Contours& p_contours,
		double& p_averageReprojectionError, PerViewErrors& p_perViewReprojectionErrors,
		CvMats& p_rvecs, CvMats& p_tvecs)
	{
		p_cameraMatrix = cv::Mat::eye(cv::Size(3, 3), CV_64F);
		p_distortionCoefficients = cv::Mat::zeros(8, 1, CV_64F);
		if (m_settings->GetFlag() & CV_CALIB_FIX_ASPECT_RATIO)
		{
			p_cameraMatrix.at<double>(0, 0) = 1.0;
		}

		std::vector<Points> points(1);
		CalculateBoardCorners(points[0]);
		points.resize(p_contours.size(), points[0]);
		cv::calibrateCamera(points, p_contours, p_imageSize, p_cameraMatrix,
			p_distortionCoefficients, p_rvecs, p_tvecs);

		bool status = (cv::checkRange(p_cameraMatrix) && cv::checkRange(p_distortionCoefficients));
		//p_averageReprojectionError = ComputeReprojectionErrors(p_cameraMatrix,
		//	p_distortionCoefficients, p_contours,
		//	p_perViewReprojectionErrors,
		//	p_rvecs, p_tvecs, points);

		return status;
	}

	void Calibration::CalculateBoardCorners(Points& p_points)
	{
		p_points.clear();
		switch (m_settings->GetCalibrationPattern())
		{
		case CalibrationSettings::Pattern::CHESSBOARD:
		case CalibrationSettings::Pattern::CIRCLES_GRID:
			for (int i = 0; i < m_settings->GetBoardHeight(); ++i)
			{
				for (int j = 0; j < m_settings->GetBoardWidth(); ++j)
				{
					p_points.push_back(cv::Point3f(
						static_cast<float>(j * m_settings->GetSquareSize()),
						static_cast<float>(i * m_settings->GetSquareSize()),
						0.0f));
				}
			}
			break;

		case CalibrationSettings::Pattern::ASYMMETRIC_CIRCLES_GRID:
			for (int i = 0; i < m_settings->GetBoardHeight(); ++i)
			{
				for (int j = 0; j < m_settings->GetBoardWidth(); ++j)
				{
					p_points.push_back(cv::Point3f(
						static_cast<float>(((2 * j) + (i % 2)) * m_settings->GetSquareSize()),
						static_cast<float>(i * m_settings->GetSquareSize()),
						0.0f));
				}
			}
			break;
		}
	}

	double Calibration::ComputeReprojectionErrors(cv::Mat& p_cameraMatrix,
		cv::Mat& p_distortionCoefficients, Contours& p_contours,
		PerViewErrors& p_perViewReprojectionErrors,
		CvMats& p_rvecs, CvMats& p_tvecs, std::vector<Points>& p_points)
	{
		Corners corners;
		double numErrors = 0.0;
		int numPoints = 0;

		p_perViewReprojectionErrors.resize(p_points.size());
		for (unsigned int i = 0; i < p_points.size(); ++i)
		{
			cv::projectPoints(cv::Mat(p_points[i]), p_rvecs[i], p_tvecs[i],
				p_cameraMatrix, p_distortionCoefficients, corners);
			double error = cv::norm(cv::Mat(p_points[i]), cv::Mat(corners[i]), CV_L2);

			unsigned int pointsSize = p_points[i].size();
			p_perViewReprojectionErrors[i] = static_cast<float>(std::sqrt((error * error) / pointsSize));
			numErrors += (error * error);
			numPoints += pointsSize;
		}

		return std::sqrt(numErrors / numPoints);
	}

	void Calibration::SaveParams(cv::Size& p_imageSize, cv::Mat& p_cameraMatrix,
		cv::Mat& p_distortionCoefficients, Contours& p_contours,
		double& p_averageReprojectionError, PerViewErrors& p_perViewReprojectionErrors,
		CvMats& p_rvecs, CvMats& p_tvecs)
	{
		m_params->SetNumberOfFrames(m_settings->GetNumberOfFrames());
		m_params->SetImageWidth(p_imageSize.width);
		m_params->SetImageHeight(p_imageSize.height);
		m_params->SetBoardWidth(m_settings->GetBoardWidth());
		m_params->SetBoardHeight(m_settings->GetBoardHeight());
		m_params->SetSquareSize(static_cast<float>(m_settings->GetSquareSize()));
		if (m_settings->GetFlag() & CV_CALIB_FIX_ASPECT_RATIO)
		{
			m_params->SetAspectRatio(m_settings->GetAspectRatio());
		}
		m_params->SetFlag(m_settings->GetFlag());
		m_params->SetCameraMatrix(p_cameraMatrix);
		m_params->SetDistortionCoefficients(p_distortionCoefficients);
		m_params->SetAverageReprojectionError(p_averageReprojectionError);
		if (!p_perViewReprojectionErrors.empty())
		{
			m_params->SetPerViewReprojectionErrors(cv::Mat(p_perViewReprojectionErrors));
		}
		if (!p_rvecs.empty() && !p_tvecs.empty())
		{
			CV_Assert(p_rvecs[0].type() == p_tvecs[0].type());
			cv::Mat bigmat((int) p_rvecs.size(), 6, p_rvecs[0].type());
			for (int i = 0; i < (int) p_rvecs.size(); i++)
			{
				cv::Mat r = bigmat(cv::Range(i, i + 1), cv::Range(0, 3));
				cv::Mat t = bigmat(cv::Range(i, i + 1), cv::Range(3, 6));

				CV_Assert(p_rvecs[i].rows == 3 && p_rvecs[i].cols == 1);
				CV_Assert(p_tvecs[i].rows == 3 && p_tvecs[i].cols == 1);
				//*.t() is MatExpr (not Mat) so we can use assignment operator
				r = p_rvecs[i].t();
				t = p_tvecs[i].t();
			}
			m_params->SetExtrinsicParameters(bigmat);
		}
		if (!p_contours.empty())
		{
			cv::Mat imagePtMat((int) p_contours.size(), (int) p_contours[0].size(), CV_32FC2);
			for (int i = 0; i < (int) p_contours.size(); i++)
			{
				cv::Mat r = imagePtMat.row(i).reshape(2, imagePtMat.cols);
				cv::Mat imgpti(p_contours[i]);
				imgpti.copyTo(r);
			}
			m_params->SetImagePoints(imagePtMat);
		}

		// TODO: uncomment
		//// Actually save
		//m_params->Save();
	}
}