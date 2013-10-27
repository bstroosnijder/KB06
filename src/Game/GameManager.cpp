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
			
			m_gameSatus = GameStatus::ATTACKER_PLACE_PENCILS;
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
		m_sceneManager->drawAll();
		m_playground->Render();
		m_gui->UpdateGui(m_playground->GetWaveNumber(), m_playground->GetAmountOfCreatures(), m_videoDriver->getFPS(), m_playground->GetPlayerHealth(), m_playground->GetPlayerResources());
	}

	void GameManager::SetupCamera()
	{
		// Create a static camera
		m_camera = m_sceneManager->addCameraSceneNode(NULL,
			irr::core::vector3df(0.0f, 0.0f, 0.0f),
			irr::core::vector3df(0.0f, 0.0f, 1.0f));

		//// Or a FPS camera
		//m_camera = m_sceneManager->addCameraSceneNodeFPS();
		//m_camera->setPosition(irr::core::vector3df(0.0f, 100.0f, -20.0f));
		//m_camera->setRotation(irr::core::vector3df(0.0f, 0.0f, 70.0f));
		//m_camera->setInputReceiverEnabled(false);
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

	}

	void GameManager::OnCreatureReachedCastle()
	{
		if (m_gameSatus == GameStatus::WAVE_RUNNING)
		{
			if (m_player1 == PlayerType::TYPE_ATTACKER)
			{
				m_scoreManager.CastleReached(0);
			}
			else
			{
				m_scoreManager.CastleReached(0);
			}
		}
	}

	void GameManager::OnCreatureKilled()
	{
		if (m_gameSatus == GameStatus::WAVE_RUNNING)
		{
			if (m_player1 == PlayerType::TYPE_ATTACKER)
			{
				m_scoreManager.CreatureKilled(0);
			}
			else
			{
				m_scoreManager.CastleReached(0);
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
		if (m_gameSatus == GameStatus::WAVE_RUNNING)
		{
			m_gameSatus = GameStatus::ATTACKER_PLACE_PENCILS;
		}
	}

	void GameManager::OnStopGame()
	{

	}

	void GameManager::OnStartWave()
	{

	}

	void GameManager::OnPlacePencils()
	{

	}

	void GameManager::OnPlaceTowers()
	{

	}

	void GameManager::OnTowerCreate()
	{

	}

	void GameManager::OnTowerDestroy()
	{

	}

	void GameManager::OnTowerUpgradeSpeed()
	{

	}

	void GameManager::OnTowerUpgradeRange()
	{

	}

	void GameManager::OnTowerUpgradeDamage()
	{

	}
}