#include "Game/GameManager.h"

namespace Game
{
	GameManager::GameManager(irr::IrrlichtDevice* p_device, irr::core::dimension2du p_resolution)
	{
		Utility::Logger* logger = Utility::Logger::GetInstance();

		m_device = p_device;
		m_resolution = p_resolution;

		if (m_device != NULL)
		{
			m_sceneManager = p_device->getSceneManager();
			m_videoDriver = p_device->getVideoDriver();
			SetupCamera();

			// Create a root scene node
			m_sceneManager->addEmptySceneNode(NULL, C_EMPTY_ROOT_SCENENODE);
			
			m_gameStatus = GameStatus::GAME_STARTED;
			m_player1 = PlayerType::TYPE_DEFENDER;
			m_playground = new Playground(this, m_sceneManager);
			m_gui = new Gui(m_device->getGUIEnvironment());
			m_eventHandler = new EventHandler(this, m_device, m_gui, m_playground);
			m_deltaTimer = new DeltaTimer(p_device->getTimer());

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
		StopGame();
	}

	void GameManager::StopGame()
	{
		/*
		delete m_playground;
		delete m_gui;
		delete m_eventHandler;
		delete m_deltaTimer;
		*/
		m_device->closeDevice();
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
		m_gui->endGame(m_gameStatus);
		m_sceneManager->drawAll();
		m_playground->Render();
		m_gui->UpdateGui(m_playground->GetWaveNumber(), m_playground->GetAmountOfCreatures(), m_videoDriver->getFPS(), m_playground->GetPlayerHealth(), m_playground->GetPlayerResources());
	}

	void GameManager::SetupCamera()
	{
		// Create a static camera
		/*m_camera = m_sceneManager->addCameraSceneNode(NULL,
			irr::core::vector3df(0.0f, 0.0f, 0.0f),
			irr::core::vector3df(0.0f, 0.0f, 1.0f));*/

		// Or a FPS camera
		m_camera = m_sceneManager->addCameraSceneNodeFPS();
		m_camera->setPosition(irr::core::vector3df(0.0f, 100.0f, -20.0f));
		m_camera->setRotation(irr::core::vector3df(0.0f, 0.0f, 70.0f));
		m_camera->setInputReceiverEnabled(false);
	}

	irr::IEventReceiver* GameManager::GetEventReceiver()
	{
		return m_eventHandler;
	}

	irr::video::ITexture* GameManager::GetCameraTexture()
	{
		return m_videoDriver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "capture_background");
	}

	void GameManager::SetCameraHeight(float p_cameraHeight)
	{
		m_camera->setPosition(
			irr::core::vector3df(0.0f, p_cameraHeight, 0.0f));
	}

	void GameManager::SetGameLength(float p_gameLength)
	{
		// TODO: Implementatie
	}

	void GameManager::SetCaptureResolution(irr::core::dimension2du p_captureResolution)
	{
		m_captureResolution = p_captureResolution;
	}
	
	irr::scene::ISceneNode* GameManager::GetRootSceneNode()
	{
		return m_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE);
	}

	void GameManager::DrawCameraTexture()
	{
		m_videoDriver->draw2DImage(m_videoDriver->getTexture("capture_background"),
			irr::core::rect<irr::s32>(0.0f, 0.0f, m_resolution.Width, m_resolution.Height),
			irr::core::rect<irr::s32>(0.0f, 0.0f, m_captureResolution.Width, m_captureResolution.Height));
	}

	irr::core::matrix4 GameManager::GetCameraProjectionMatrix()
	{
		return m_camera->getProjectionMatrix();
	}

	bool GameManager::IsLookingForPencilCoords()
	{
		return (m_gameStatus == GameStatus::ATTACKER_PLACE_PENCILS);
	}

	void SetPencilCoords(irr::core::vector3df* p_points1,
			irr::core::vector3df* p_points2,
			int p_amount)
	{

	}

	void GameManager::BeginScene()
	{
		m_videoDriver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));
	}

	void GameManager::EndScene()
	{
		m_videoDriver->endScene();
	}

	void GameManager::OnCreatureSpawned()
	{
		if (m_gameStatus == GameStatus::WAVE_RUNNING)
		{

		}
	}

	void GameManager::OnCreatureReachedCastle()
	{
		if (m_gameStatus == GameStatus::WAVE_RUNNING)
		{
			if (m_player1 == PlayerType::TYPE_ATTACKER)
			{
				m_scoreManager.CastleReached(0);
			}
			else
			{
				m_scoreManager.CastleReached(1);
			}
		}
	}

	void GameManager::OnCreatureKilled()
	{
		if (m_gameStatus == GameStatus::WAVE_RUNNING)
		{
			if (m_player1 == PlayerType::TYPE_ATTACKER)
			{
				m_scoreManager.CreatureKilled(0);
			}
			else
			{
				m_scoreManager.CreatureKilled(1);
			}
		}
	}

	void GameManager::OnCreatureHit()
	{

	}

	void GameManager::OnProjectileMissed()
	{

	}

	void GameManager::OnProjectileFired()
	{

	}

	void GameManager::OnWaveEnded()
	{
		if (m_gameStatus == GameStatus::WAVE_RUNNING)
		{
			m_gameStatus = GameStatus::WAVE_FINISHED;
			m_gui->SetButtonAttackersTurnEnabled(true);
		}
	}

	void GameManager::OnStopGame()
	{
		StopGame();
	}

	void GameManager::OnStartWave()
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			m_playground->StartNextWave();

			m_gui->SetButtonDefendersActionsEnabled(false);
			m_gui->SetButtonStartWaveEnabled(false);

			m_gameStatus = GameStatus::WAVE_RUNNING;
		}
	}

	void GameManager::OnPlacePencils()
	{
		if (m_gameStatus == GameStatus::WAVE_FINISHED || m_gameStatus == GameStatus::GAME_STARTED)
		{
			m_gui->SetButtonAttackersTurnEnabled(false);
			m_gui->SetButtonAttackersActionsEnabled(true);
			m_gui->SetButtonDefendersTurnEnabled(true);

			m_gameStatus = GameStatus::ATTACKER_PLACE_PENCILS;
		}
	}

	void GameManager::OnBuyPencil()
	{

	}

	void GameManager::OnPlaceTowers()
	{
		if (m_gameStatus == GameStatus::ATTACKER_PLACE_PENCILS)
		{
			m_gui->SetButtonAttackersActionsEnabled(false);
			m_gui->SetButtonDefendersTurnEnabled(false);
			m_gui->SetButtonDefendersActionsEnabled(true);
			m_gui->SetButtonStartWaveEnabled(true);
			
			m_gameStatus = GameStatus::DEFENDER_PLACE_TOWERS;
		}
	}

	void GameManager::OnTowerCreate(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			m_playground->SpawnTower(p_position);
		}
	}

	void GameManager::OnTowerDestroy(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			m_playground->SellTower(p_position);
		}
	}

	void GameManager::OnTowerUpgradeSpeed(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			m_playground->UpgradeTowerSpeed(p_position);
		}
	}

	void GameManager::OnTowerUpgradeRange(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			m_playground->UpgradeTowerRange(p_position);
		}
	}

	void GameManager::OnTowerUpgradeDamage(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			m_playground->UpgradeTowerDamage(p_position);
		}
	}
}