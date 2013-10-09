#include "Game/Kernel.h"
#include "Game/Tower.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1280, 720));
		m_videoDriver = m_device->getVideoDriver();
		m_sceneManager = m_device->getSceneManager();
		m_deltaTimer = new DeltaTimer(m_device->getTimer());	
	
		//m_capture = new Camera::Capture(m_videoDriver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "capture_background"));
		m_capture = NULL;

		// The L is needed to have a long string. Irrlicht uses this. 
		m_device->setWindowCaption(L"KB01: Game");
		
		m_camera = m_sceneManager->addCameraSceneNodeFPS();
		m_camera->setPosition(irr::core::vector3df(0.0f, 100.0f, -20.0f));
		m_camera->setRotation(irr::core::vector3df(0.0f, 0.0f, 70.0f));
		m_camera->setInputReceiverEnabled(false);
		m_device->getCursorControl()->setVisible(true);

		m_playground = new Playground(m_sceneManager);

		m_gui = new Game::Gui(m_device->getGUIEnvironment());
		Game::EventHandler* eventHandler = new Game::EventHandler(m_device,m_gui,m_playground);
		m_device->setEventReceiver(eventHandler);
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
		while (m_device->run())
		{
			// Update the texture with the camera capture
			//m_capture->Update();

			m_videoDriver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));

			//m_videoDriver->draw2DImage(m_videoDriver->getTexture("capture_background"), irr::core::vector2d<irr::s32>(0, 0));
			m_playground->Update(m_sceneManager, m_deltaTimer->GetDelta());
			m_playground->Render(m_sceneManager);
			
			m_sceneManager->drawAll();
			m_gui->UpdateGui(m_playground->returnWaveNumber(),m_playground->returnAmountOfCreatures(),m_videoDriver->getFPS());
			m_videoDriver->endScene();

			ShowFPS();
		}
	}

	void Kernel::ShowFPS()
	{
		irr::core::stringw title = "KB01: Game";
		title += " - FPS: ";
		title += m_videoDriver->getFPS();

		m_device->setWindowCaption(title.c_str());
	}
}