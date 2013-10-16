#include "Game/GameManager.h"

namespace Game
{
	GameManager::GameManager(irr::IrrlichtDevice* p_device)
	{
		Utility::Logger* logger = Utility::Logger::GetInstance();

		m_device = p_device;

		if (m_device != NULL)
		{
			m_sceneManager = p_device->getSceneManager();
			m_videoDriver = p_device->getVideoDriver();
			SetupCamera();

			m_playground = new Playground(m_sceneManager);
			m_gui = new Gui(m_device->getGUIEnvironment());
			m_eventHandler = new EventHandler(m_device, m_gui, m_playground);
			m_deltaTimer = new DeltaTimer(p_device->getTimer());

			m_device->setEventReceiver(m_eventHandler);
			m_device->setWindowCaption(L"KB06: Game");
			m_device->getCursorControl()->setVisible(true);		

			logger->Log(Utility::Logger::LOG_MESSAGE, "Startin game: Successful Started", __LINE__, __FILE__);
		}
		else
		{
			logger->Log(Utility::Logger::LOG_ERROR, "Starting game: Failed", __LINE__, __FILE__);
		}
	}

	GameManager::~GameManager()
	{
		delete m_playground;
		delete m_deltaTimer;

		m_playground = NULL;
		m_deltaTimer = NULL;
	}

	void GameManager::GameTick()
	{
		Update();
		Render();
	}

	void GameManager::Update()
	{
		m_playground->Update(m_deltaTimer->GetDelta());
	}

	void GameManager::Render()
	{
		m_gui->endGame(m_playground->GetGameStatus());
		m_videoDriver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));
		{
			m_sceneManager->drawAll();
			m_playground->Render();
			m_gui->UpdateGui(m_playground->GetWaveNumber(),m_playground->GetAmountOfCreatures(),m_videoDriver->getFPS(), m_playground->GetPlayerHealth(), m_playground->GetPlayerResources());
			
		}
		m_videoDriver->endScene();
	}

	void GameManager::SetupCamera()
	{
		m_camera = m_sceneManager->addCameraSceneNodeFPS();
		m_camera->setPosition(irr::core::vector3df(0.0f, 100.0f, -20.0f));
		m_camera->setRotation(irr::core::vector3df(0.0f, 0.0f, 70.0f));
		m_camera->setInputReceiverEnabled(false);
	}

	irr::IEventReceiver* GameManager::GetEventReceiver()
	{
		return m_eventHandler;
	}
}