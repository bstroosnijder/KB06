#include "Game/Kernel.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1280, 720));

		if (!m_device)
		{
			Utility::Logger* logger = Utility::Logger::GetInstance();
			logger->Log(Utility::Logger::LogMessageType::LOG_ERROR, "Failed to create IDevice");
			return;
		}

		m_inputHandler = new InputHandler();
		m_device->setEventReceiver(m_inputHandler);
		m_gameManager = new GameManager(m_device);
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

		m_device->drop();
	}

	void Kernel::Start()
	{
		// Gets the root scene node
		irr::scene::ISceneNode* root = m_gameManager->GetRootSceneNode();
		// Capture class
		Camera::Capture* capture = new Camera::Capture(m_multiThreaded, m_gameManager->GetCameraTexture());
		m_inputHandler->AddListener(capture);
		capture->SetFov(60);
		capture->SetLongestGameLine(irr::core::line2df(
			irr::core::vector2df(0.0, 0.0),
			irr::core::vector2df(0.0, 100.0f)));

		while (m_device->run())
		{
			capture->Start();
			m_gameManager->SetCameraHeight(capture->GetPixelDistance());
			// TODO GetCalculatedShortestGameLine: rename
			m_gameManager->SetGameLength(capture->GetCalculatedShortestGameLine().getLength());
			
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

					//irr::core::matrix4 transformation = m_capture->GetTransformMatrix(m_gameManager->GetCameraProjectionMatrix());
					//root->setPosition(transformation.getTranslation());
					//root->setRotation(transformation.getRotationDegrees());
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