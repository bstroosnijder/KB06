#include "Game/Kernel.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_title = "KB06: Game";
		m_multiThreaded = false;
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1280, 720));
		m_videoDriver = m_device->getVideoDriver();
		m_sceneManager = m_device->getSceneManager();
		m_deltaTimer = new DeltaTimer(m_device->getTimer());
	
		// The L is needed to have a long string. Irrlicht uses this. 
		m_device->setWindowCaption(m_title.c_str());
		// Set the cursor to visible
		m_device->getCursorControl()->setVisible(true);

		m_playground = new Playground(m_sceneManager);
		m_gui = new Game::Gui(m_device->getGUIEnvironment());

		// Input listener observer
		m_inputHandler = new InputHandler();
		m_device->setEventReceiver(m_inputHandler);
		m_inputHandler->AddListener(new EventHandler(m_device, m_gui, m_playground));
	}

	Kernel::~Kernel()
	{
		Cleanup();
	}

	void Kernel::Cleanup()
	{
		if (m_capture != NULL)
		{
			delete m_capture;
		}

		m_device->drop();
		delete m_deltaTimer;
	}

	void Kernel::Start()
	{
		// Create a webcam capturer
		m_capture = new Camera::Capture(m_multiThreaded, m_videoDriver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "capture_background"));
		m_capture->SetFov(60.0f);
		m_capture->SetLongestGameLine(irr::core::line2df(
			irr::core::vector2df(0, 0),
			irr::core::vector2df(0, 400)));
		// Adds the capturer to the input listener
		m_inputHandler->AddListener(m_capture);

		// Create a root node for all other nodes to inherit the AR movement
		irr::scene::ISceneNode* root = m_sceneManager->addEmptySceneNode(NULL, C_EMPTY_ROOT_SCENENODE);

		// Create a static camera
		irr::scene::ICameraSceneNode* camera = m_sceneManager->addCameraSceneNode(NULL,
			irr::core::vector3df(0.0f, m_capture->GetPixelDistance(), 1.0f),
			irr::core::vector3df(0.0f, 0.0f, 0.0f));

		// Or an FPS camera
		//irr::scene::ICameraSceneNode* camera = m_sceneManager->addCameraSceneNodeFPS();
		//camera->setPosition(irr::core::vector3df(0.0f, 100.0f, -20.0f));
		//camera->setRotation(irr::core::vector3df(0.0f, 0.0f, 70.0f));
		//camera->setInputReceiverEnabled(false);

		// TEH game loop yo!
		while (m_device->run())
		{
			// Start the capture thread
			m_capture->Start();
			// Update the camera height
			camera->setPosition(
				irr::core::vector3df(0.0f, m_capture->GetPixelDistance(), 1.0f));
			// Update the games shortest side
			m_capture->GetCalculatedShortestGameLine();
			// gui something? TODO
			m_gui->endGame(m_playground->GetGameStatus());

			// BEGIN
			m_videoDriver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));
			// Updates the playground
			m_playground->Update(m_deltaTimer->GetDelta());
			// Renders the playground
			m_playground->Render();
			// Update the gui
			m_gui->UpdateGui(m_playground->GetWaveNumber(), m_playground->GetAmountOfCreatures(), m_videoDriver->getFPS(), m_playground->GetPlayerHealth(), m_playground->GetPlayerResources());
			
			// Draw the camera in the screen
			m_videoDriver->draw2DImage(m_videoDriver->getTexture("capture_background"), irr::core::vector2d<irr::s32>(0, 0));
			if (m_capture->HasChosen())
			{
				if (m_capture->IsLost() == false)
				{
					if (m_inputHandler->Contains(m_capture))
					{
						m_inputHandler->RemoveListener(m_capture);
					}

					// Get the transformation matrix needed to transform the world based on the AR
					irr::core::matrix4 transformation = m_capture->GetTransformMatrix(camera->getProjectionMatrix());
					root->setPosition(transformation.getTranslation());
					root->setRotation(transformation.getRotationDegrees());
				}

				// Actually draw the scene, but only once the playground surface has been chosen
				m_sceneManager->drawAll();
			}
			
			// END
			m_videoDriver->endScene();
		}
	}

	void Kernel::SetMultiThreaded(bool p_multiThreaded)
	{
		m_multiThreaded = p_multiThreaded;
	}

	void Kernel::ShowFPS()
	{
		irr::core::stringw title = m_title;
		title += " - FPS: ";
		title += m_videoDriver->getFPS();

		m_device->setWindowCaption(title.c_str());
	}
}