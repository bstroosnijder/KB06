#ifndef __GAME__GAMEMANAGER__H__
#define __GAME__GAMEMANAGER__H__

#include "Defines.h"
#include "GameListener.h"
#include "GameStatus.h"
#include "PlayerType.h"
#include "ScoreManager.h"
#include "Playground.h"
#include "DeltaTimer.h"
#include "EventHandler.h"
#include "Utility/Logger.h"

#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	TODO
	 *			
	 * @author	Alex Hodes
	 */
	class GameManager : public GameListener, UserInputListener
	{
	public:
		GameManager(irr::IrrlichtDevice* p_device, irr::core::dimension2du p_resolution);
		~GameManager();

		void StopGame();
		void GameTick();

		irr::IEventReceiver* GetEventReceiver();
		irr::video::ITexture* GetCameraTexture();
		void SetCameraHeight(float p_cameraHeight);
		void SetGameLength(float p_gameLength);
		void SetCaptureResolution(irr::core::dimension2du p_captureResolution);
		irr::scene::ISceneNode* GetRootSceneNode();
		void DrawCameraTexture();
		irr::core::matrix4 GetCameraProjectionMatrix();
		bool IsLookingForPencilCoords();
		void SetPencilCoords(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_amount);
		void BeginScene();
		void EndScene();
		
		//GameListenerEvents.
		void OnCreatureSpawned();
		void OnCreatureReachedCastle();
		void OnCreatureKilled();
		void OnCreatureHit();
		void OnProjectileMissed();
		void OnProjectileFired();
		void OnWaveEnded();

		//UserInputListenerEvents.
		void OnStopGame();
		void OnStartWave();
		void OnPlacePencils();
		void OnBuyPencil();
		void OnPlaceTowers();
		void OnTowerCreate(irr::core::vector2di p_position);
		void OnTowerDestroy(irr::core::vector2di p_position);
		void OnTowerUpgradeSpeed(irr::core::vector2di p_position);
		void OnTowerUpgradeRange(irr::core::vector2di p_position);
		void OnTowerUpgradeDamage(irr::core::vector2di p_position);


		float GetGameHeight();

	private:
		irr::IrrlichtDevice* m_device;
		irr::core::dimension2du m_resolution;
		irr::core::dimension2du m_captureResolution;
		irr::scene::ISceneManager* m_sceneManager;
		irr::video::IVideoDriver* m_videoDriver;
		irr::scene::ICameraSceneNode* m_camera;

		ScoreManager m_scoreManager;
		GameStatus m_gameStatus;
		PlayerType m_player1;
		Playground* m_playground;
		Gui* m_gui;
		EventHandler* m_eventHandler;
		DeltaTimer* m_deltaTimer;

		//TODO comments
		/**
		 * @brief TODO
		 */
		void Update();

		/**
		 * @brief TODO
		 */
		void Render();

		/**
		 * @brief TODO
		 */
		void SetupCamera();
	};
}

#endif