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

			logger->Log(Utility::Logger::LOG_MESSAGE, "Starting game: Successful Started", __LINE__, __FILE__);
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

	/// @todo Check closing sequence?
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
		if (m_gameStatus == GameStatus::WAVE_RUNNING)
		{
			m_playground->Update(m_deltaTimer->GetDelta());
		}
	}

	void GameManager::Render()
	{
		m_sceneManager->drawAll();
		m_playground->Render();
		m_gui->UpdateGui(m_playground->GetWaveNumber(),
				m_playground->GetWaveSize(),
				m_playground->GetCreaturesSpawned(),
				m_videoDriver->getFPS(),
				m_scoreManager.GetPlayerScore(0),
				m_scoreManager.GetPlayerScore(1));
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
		m_playground->UpdateGameScale(p_gameLength);

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
			irr::core::recti(0, 0, m_resolution.Width, m_resolution.Height),
			irr::core::recti(0, 0, m_captureResolution.Width, m_captureResolution.Height));
	}

	irr::core::matrix4 GameManager::GetCameraProjectionMatrix()
	{
		return m_camera->getProjectionMatrix();
	}

	bool GameManager::IsLookingForPencilCoords()
	{
		return (m_gameStatus == GameStatus::ATTACKER_PLACE_PENCILS && m_isLookingForPencilCoords);
	}

	void GameManager::SetPencilCoords(irr::core::vector3df* p_points1, irr::core::vector3df* p_points2)
	{
		if (m_gameStatus == GameStatus::ATTACKER_PLACE_PENCILS && m_isLookingForPencilCoords)
		{
			m_playground->SetupPath(p_points1, p_points2);
			m_isLookingForPencilCoords = false;
		}
	}

	void SetPencilCoords(irr::core::vector3df* p_points1,
			irr::core::vector3df* p_points2,
			int p_amount)
	{
		
	}

	float GameManager::GetGameHeight()
	{
		return m_playground->GetPlaygroundHeight();
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

	void GameManager::OnWaveEnded()
	{
		if (m_gameStatus == GameStatus::WAVE_RUNNING)
		{
			if (m_playground->AreAllWavesFinished())
			{
				//The game has ended

				/// @todo	Determine the winner Player of the current game round.
				PlayerType gameRoundWinner = PlayerType::TYPE_ATTACKER;

				if (m_player1 == PlayerType::TYPE_ATTACKER)
				{
					//If the first Round ended

					//Show the winner of the current game round.
					m_gui->ShowVictory(gameRoundWinner);

					//Switch player sides
					m_player1 = PlayerType::TYPE_DEFENDER;
				}
				else
				{
					//If the second round ended
					
					//Show the winner of the current game round.
					m_gui->ShowVictory(gameRoundWinner);

					//Determine the winning Player of the game.
					bool player1IsWinner = m_scoreManager.GetPlayerScore(0) > m_scoreManager.GetPlayerScore(1);

					if (player1IsWinner)
					{
						//m_gui->ShowWinningPlayer(0);
					}
					else
					{
						//m_gui->ShowWinningPlayer(1);
					}
				}
			}
			else
			{
				//A new wave should start
				m_gui->SetButtonAttackersTurnEnabled(true);
				m_gameStatus = GameStatus::WAVE_FINISHED;
			}
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
		if (m_gameStatus == GameStatus::ATTACKER_PLACE_PENCILS)
		{

		}
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
			if (m_playground->CreateTower(p_position))
			{
				m_scoreManager.TowerCreated(GetPlayerNumber(PlayerType::TYPE_DEFENDER));
			}
		}
	}

	void GameManager::OnTowerDestroy(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			if (m_playground->DestroyTower(p_position))
			{
				//m_scoreManager.TowerSold();
			}
		}
	}

	void GameManager::OnTowerUpgradeSpeed(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			if (m_playground->UpgradeTowerSpeed(p_position))
			{
				//m_scoreManager.TowerUpgradedSpeed();
			}
		}
	}

	void GameManager::OnTowerUpgradeRange(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			if (m_playground->UpgradeTowerRange(p_position))
			{
				//m_scoreManager.TowerUpgradedRange();
			}
		}
	}

	void GameManager::OnTowerUpgradeDamage(irr::core::vector2di p_position)
	{
		if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			if (m_playground->UpgradeTowerDamage(p_position))
			{
				m_scoreManager.TowerIncreasedDamage(GetPlayerNumber(PlayerType::TYPE_DEFENDER));
			}
		}
	}

	int GameManager::GetPlayerNumber(PlayerType p_playerType)
	{
		/*
		m_player1		Defender
		p_playerType	Defender
		- - - - - - - - - - - -
		Result			0

		m_player1		Defender
		p_playerType	Attacker
		- - - - - - - - - - - -
		Result			1

		m_player1		Attacker
		p_playerType	Defender
		- - - - - - - - - - - -
		Result			1

		m_player1		Attacker
		p_playerType	Attacker
		- - - - - - - - - - - -
		Result			0
		*/
		return m_player1 == PlayerType::TYPE_DEFENDER ^ p_playerType;
	}
}