#include "Game/Kernel.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_title = "KB01: Game";
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(640, 480));
		m_driver = m_device->getVideoDriver();
		m_gui = m_device->getGUIEnvironment();
		m_scene = m_device->getSceneManager();
		m_inputHandler = new InputHandler();
		m_device->setEventReceiver(m_inputHandler);
		m_capture = new Camera::Capture(m_driver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "capture_background"));
		m_inputHandler->AddListener(m_capture);

		// The L is needed to have a long string. Irrlicht uses this. 
		m_device->setWindowCaption(m_title.c_str());
		m_device->setResizable(true);

		// Add a camera to the scene
		m_scene->addCameraSceneNode(NULL, irr::core::vector3df(0.0f, 100.0f, -150.0f), irr::core::vector3df(0.0f, 0.0f, 0.0f));

		// Add a test cube to the scene
		//irr::scene::ISceneNode* cube = m_scene->addCubeSceneNode(50.0f, NULL, NULL, irr::core::vector3df(0.0f, 0.0f, 0.0f));
		//cube->setMaterialTexture(0, m_driver->getTexture("resources\\textures\\purple.jpg"));
		//cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
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
			m_driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));

			// Update the texture with the camera capture
			m_capture->Update();
			m_driver->draw2DImage(m_driver->getTexture("capture_background"), irr::core::vector2d<irr::s32>(0, 0));

			if (m_capture->HasChosen() && m_capture->IsLost() == false)
			{
				if (m_inputHandler->Contains(m_capture))
				{
					m_inputHandler->RemoveListener(m_capture);
				}
				m_scene->drawAll();
			}

			m_driver->endScene();
		}
	}

	void Kernel::ShowFPS()
	{
		irr::core::stringw title = m_title;
		title += " - FPS: ";
		title += m_driver->getFPS();

		m_device->setWindowCaption(title.c_str());
	}
}