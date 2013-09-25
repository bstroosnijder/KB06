#include "Game/Kernel.h"
#include "Game/Tower.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_title = "KB06: Game";
		m_runMultiThreaded = true;
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(640, 480));
		m_videoDriver = m_device->getVideoDriver();
		m_guiEnvironment = m_device->getGUIEnvironment();
		m_sceneManager = m_device->getSceneManager();
		m_inputHandler = new InputHandler();
		m_device->setEventReceiver(m_inputHandler);
		m_capture = new Camera::Capture(m_runMultiThreaded, m_videoDriver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "capture_background"));
		m_inputHandler->AddListener(m_capture);
		m_camera = m_sceneManager->addCameraSceneNode(NULL, irr::core::vector3df(0.0f, 20.0f, -20.0f), irr::core::vector3df(0.0f, 0.0f, 0.0f));

		// The L is needed to have a long string. Irrlicht uses this. 
		m_device->setWindowCaption(m_title.c_str());
		m_device->setResizable(true);
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
		irr::scene::ISceneNode* cube = m_sceneManager->addCubeSceneNode();
		cube->setMaterialTexture(0, m_videoDriver->getTexture("resources\\textures\\purple.jpg"));
		cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);


		while (m_device->run())
		{
			// Start the capture thread
			m_capture->Start();

			// Show the fps in the title of the window
			ShowFPS();
			// Begin an empty blue scene
			m_videoDriver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));

			// Update the texture with the camera capture
			m_videoDriver->draw2DImage(m_videoDriver->getTexture("capture_background"), irr::core::vector2d<irr::s32>(0, 0));
			if (m_capture->HasChosen() && m_capture->IsLost() == false)
			{
				if (m_inputHandler->Contains(m_capture))
				{
					m_inputHandler->RemoveListener(m_capture);
				}
				// Update the camera projection matrix
				m_camera->setProjectionMatrix(m_capture->GetProjectionMatrix(m_camera->getProjectionMatrix()));
			}

			m_sceneManager->drawAll();
			m_guiEnvironment->drawAll();
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