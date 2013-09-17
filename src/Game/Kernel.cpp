#include "Game/Kernel.h"
#include "Game/Tower.h"

namespace Game
{
	Game::Tower* tower;

	Kernel::Kernel()
	{
		m_title = "KB01: Game";
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(640, 480));
		m_videoDriver = m_device->getVideoDriver();
		m_guiEnvironment = m_device->getGUIEnvironment();
		m_sceneManager = m_device->getSceneManager();
		m_inputHandler = new InputHandler();
		m_capture = NULL;

		m_device->setEventReceiver(m_inputHandler);
		// The L is needed to have a long string. Irrlicht uses this. 
		m_device->setWindowCaption(m_title.c_str());
		m_device->setResizable(true);

		//m_capture = new Camera::Capture(m_videoDriver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "capture_background"));
		//m_inputHandler->AddListener(m_capture);

		// Add a camera to the scene
		//m_sceneManager->addCameraSceneNode(0, irr::core::vector3df(0, 100, 0), irr::core::vector3df());
		m_sceneManager->addCameraSceneNodeFPS()->setPosition(irr::core::vector3df(0, 0, -100));
		//irr::scene::ISceneNode* cube = m_sceneManager->addCubeSceneNode(50.0f, NULL, NULL, irr::core::vector3df(0.0f, 0.0f, 0.0f));
		
		//tower = new Tower(m_sceneManager, irr::core::vector3df(0, 0, 0));
		//tower = new Tower(m_sceneManager, irr::core::vector3df(100, 0, 0));
	}

	Kernel::~Kernel()
	{
		Cleanup();
	}

	void Kernel::Cleanup()
	{
		if (m_capture)
		{
			delete m_capture;
		}

		m_device->drop();
	}

	void Kernel::Start()
	{
		while (m_device->run())
		{
			ShowFPS();
			m_videoDriver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));

			/*
			// Update the texture with the camera capture
			m_capture->Update();
			m_videoDriver->draw2DImage(m_videoDriver->getTexture("capture_background"), irr::core::vector2d<irr::s32>(0, 0));
			/*
			if (m_capture->HasChosen() && m_capture->IsLost() == false)
			{
				if (m_inputHandler->Contains(m_capture))
				{
					m_inputHandler->RemoveListener(m_capture);
				}
				m_sceneManager->drawAll();
			}
			*/
			
			m_sceneManager->drawAll();
			m_videoDriver->endScene();
		}
	}

	void Kernel::ShowFPS()
	{
		irr::core::stringw title = m_title;
		title += " - FPS: ";
		title += m_videoDriver->getFPS();

		m_device->setWindowCaption(title.c_str());
	}
}