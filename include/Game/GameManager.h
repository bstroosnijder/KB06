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
	 * @brief	
	 * @todo	Write ALL comments (which is ALOT!!!!)
	 *			
	 * @author	Alex Hodes, Leon van Egmond
	 */
	class GameManager : public GameListener, UserInputListener
	{
	public:
	   /**
		* @brief constructs the gamemanager
		* @param p_device		the rendering videodevice
		* @param p_resolution	the window resolutu=ion	
		*/
		GameManager(irr::IrrlichtDevice* p_device, irr::core::dimension2du p_resolution);

	   /**
		* @brief destructs the gamemanager
		*/
		~GameManager();

	   /**
	    * @todo
		*/
		void StopGame();

	   /**
	    * @todo
		*/
		void GameTick();

	   /**
	    * @todo
		*/
		irr::IEventReceiver* GetEventReceiver();

	   /**
	    * @todo
		*/
		irr::video::ITexture* GetCameraTexture();

	   /**
	    * @todo
		*/
		void SetCameraHeight(float p_cameraHeight);

	   /**
	    * @todo
		*/
		void SetGameLength(float p_gameLength);

	   /**
	    * @todo
		*/
		void SetCaptureResolution(irr::core::dimension2du p_captureResolution);

	   /**
	    * @todo
		*/
		irr::scene::ISceneNode* GetRootSceneNode();

	   /**
	    * @todo
		*/
		void DrawCameraTexture();

	   /**
	    * @todo
		*/
		irr::core::matrix4 GetCameraProjectionMatrix();

	   /**
	    * @todo
		*/
		bool IsLookingForPencilCoords();

	   /**
	    * @todo
		*/
		void SetPencilCoords(irr::core::vector3df* m_points1,
				irr::core::vector3df* m_points2);

	   /**
	    * @todo
		*/
		void SetPencilCoords(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_amount);

	   /**
	    * @todo
		*/
		void BeginScene();

	   /**
	    * @todo
		*/
		void EndScene();
		
		//GameListenerEvents.
	   /**
	    * @todo
		*/
		void OnCreatureSpawned();

	   /**
	    * @todo
		*/
		void OnCreatureReachedCastle();

	   /**
	    * @todo
		*/
		void OnCreatureKilled();

	   /**
	    * @todo
		*/
		void OnCreatureHit();

	   /**
	    * @todo
		*/
		void OnProjectileMissed();

	   /**
	    * @todo
		*/
		void OnProjectileFired();

	   /**
	    * @todo
		*/
		void OnWaveEnded();

		//UserInputListenerEvents.
	   /**
	    * @todo
		*/
		void OnStopGame();

	   /**
	    * @todo
		*/
		void OnStartWave();

	   /**
	    * @todo
		*/
		void OnPlacePencils();

	   /**
	    * @todo
		*/
		void OnCapturePencils();

	   /**
	    * @todo
		*/
		void OnBuyPencil();

	   /**
	    * @todo
		*/
		void OnPlaceTowers();

	   /**
	    * @todo
		*/
		void OnTowerCreate(irr::core::vector2di p_position);

	   /**
	    * @todo
		*/
		void OnTowerDestroy(irr::core::vector2di p_position);

	   /**
	    * @todo
		*/
		void OnTowerUpgradeSpeed(irr::core::vector2di p_position);

	   /**
	    * @todo
		*/
		void OnTowerUpgradeRange(irr::core::vector2di p_position);

	   /**
	    * @todo
		*/
		void OnTowerUpgradeDamage(irr::core::vector2di p_position);

	   /**
	    * @todo
		*/
		float GetGameHeight();

	private:
		irr::IrrlichtDevice* m_device;
		irr::core::dimension2du m_resolution;
		irr::core::dimension2du m_captureResolution;
		irr::scene::ISceneManager* m_sceneManager;
		irr::video::IVideoDriver* m_videoDriver;
		irr::scene::ICameraSceneNode* m_camera;
		irr::scene::ICameraSceneNode* m_cameraFPS;

		ScoreManager m_scoreManager;
		GameStatus m_gameStatus;
		PlayerType m_player1;
		Playground* m_playground;
		Gui* m_gui;
		EventHandler* m_eventHandler;
		DeltaTimer* m_deltaTimer;


		bool m_isLookingForPencilCoords;

		
		/**
		 * @todo
		 */
		void Update();

		/**
		 * @todo
		 */
		void Render();

		/**
		 * @todo
		 */
		void SetupCamera();

	   /**
	    * @todo
		*/
		int GetPlayerNumber(PlayerType p_playerType);
	};
}

#endif