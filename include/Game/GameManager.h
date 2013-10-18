#ifndef __GAME__GAMEMANAGER__H__
#define __GAME__GAMEMANAGER__H__

#include "Defines.h"
#include "GameListener.h"
#include "ScoreManager.h"
#include "Playground.h"
#include "DeltaTimer.h"
#include "EventHandler.h"
#include "Utility/Logger.h"

#include <irrlicht.h>

namespace Game
{
	class GameManager : public GameListener
	{
	public:
		GameManager(irr::IrrlichtDevice* p_device, irr::core::dimension2du p_resolution);
		~GameManager();

		void GameTick();
		irr::IEventReceiver* GetEventReceiver();
		irr::video::ITexture* GetCameraTexture();
		void SetCameraHeight(float p_cameraHeight);
		void SetGameLength(float p_gameLength);
		void SetCaptureResolution(irr::core::dimension2du p_captureResolution);
		irr::scene::ISceneNode* GetRootSceneNode();
		void DrawCameraTexture();
		irr::core::matrix4 GetCameraProjectionMatrix();
		void BeginScene();
		void EndScene();
		
		void CreatureSpawned();
		void CreatureReachedCastle();
		void CreatureKilled();
		void CreatureHit();
		void ProjectileMissed();
		void ProjectileFired();
		void WaveEnded();

	private:
		irr::IrrlichtDevice* m_device;
		irr::core::dimension2du m_resolution;
		irr::core::dimension2du m_captureResolution;
		irr::scene::ISceneManager* m_sceneManager;
		irr::video::IVideoDriver* m_videoDriver;
		irr::scene::ICameraSceneNode* m_camera;

		ScoreManager m_scoreManager;
		int m_player1;
		Playground* m_playground;
		Gui* m_gui;
		EventHandler* m_eventHandler;
		DeltaTimer* m_deltaTimer;
		
		void Update();
		void Render();
		void SetupCamera();
	};
}

#endif