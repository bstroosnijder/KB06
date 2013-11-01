#include "Game/Kernel.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_resolution = irr::core::dimension2du(1280, 960);
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, m_resolution);

		if (!m_device)
		{
			Utility::Logger* logger = Utility::Logger::GetInstance();
			logger->Log(Utility::Logger::LogMessageType::LOG_ERROR, "Failed to create IDevice");
			return;
		}

		m_inputHandler = new InputHandler();
		m_device->setEventReceiver(m_inputHandler);
		m_gameManager = new GameManager(m_device, m_resolution);
		m_inputHandler->AddListener(m_gameManager->GetEventReceiver());
	}

	Kernel::~Kernel()
	{
		Cleanup();
	}

	void Kernel::Cleanup()
	{
		if (m_inputHandler != NULL)
		{
			delete m_inputHandler;
			m_inputHandler = NULL;
		}

		if (m_gameManager != NULL)
		{
			delete m_gameManager;
			m_gameManager = NULL;
		}

		if (m_device != NULL)
		{
			//irr::core::IDevice::drop() deletes everything.
			m_device->drop();
			m_device = NULL;
		}
	}

	void Kernel::Start()
	{
		// Gets the root scene node
		irr::scene::ISceneNode* root = m_gameManager->GetRootSceneNode();
		//// Capture class
		Camera::Capture* capture = new Camera::Capture(m_multiThreaded, m_resolution, m_gameManager->GetCameraTexture());
		m_inputHandler->AddListener(capture);
		capture->SetFov(60);
		capture->SetShortestGameLine(irr::core::line2df(
			irr::core::vector2df(0.0f, 0.0f),
			irr::core::vector2df(0.0f, m_gameManager->GetGameHeight())));
		
		// Sets the resolution of the camera for the scaling of the background
		m_gameManager->SetCaptureResolution(capture->GetCaptureSize());
		
		while (m_device->run())
		{
			capture->Start();
			m_gameManager->SetCameraHeight(capture->GetPixelDistance());
			m_gameManager->SetGameLength(capture->GetCalculatedLongestGameLine().getLength());

			// Begin the scene
			m_gameManager->BeginScene();
			// Always draw the camera background
			m_gameManager->DrawCameraTexture();
			
			if (capture->HasChosen())
			{
				if (capture->IsLost() == false)
				{
					if (m_inputHandler->Contains(capture))
					{
						m_inputHandler->RemoveListener(capture);
					}

					// Gets the transformation matrix and sets it on the root matrix
					irr::core::matrix4 transformation = capture->GetTransformMatrix(m_gameManager->GetCameraProjectionMatrix());
					root->setPosition(transformation.getTranslation());
					root->setRotation(transformation.getRotationDegrees());
					root->setScale(transformation.getScale());

				}
				if (m_gameManager->IsLookingForPencilCoords())
				{
					irr::core::vector3df* startPoints = NULL;
					irr::core::vector3df* endPoints = NULL;
					int pencilCount = capture->FindStartAndEndPoints(capture->GetImage(), m_gameManager->GetCameraProjectionMatrix(), startPoints, endPoints);

					if (pencilCount > 0)
					{
						m_gameManager->SetPencilCoords(startPoints, endPoints, pencilCount);
					}

					delete[] startPoints;
					delete[] endPoints;
				}

				// Actually draw the scene, but only once the playground surface has been chosen
				m_gameManager->GameTick();
			
			}
			// End the scene
			m_gameManager->EndScene();
		}

		// Cleanup the capture
		delete capture;
	}

	void Kernel::SetMultiThreaded(bool p_multiThreaded)
	{
		m_multiThreaded = p_multiThreaded;
	}
}