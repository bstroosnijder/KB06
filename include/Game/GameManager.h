#ifndef __GAME__GAMEMANAGER__H__
#define __GAME__GAMEMANAGER__H__

#include "Defines.h"
#include "Playground.h"
#include "DeltaTimer.h"
#include "EventHandler.h"
#include "Utility/Logger.h"

#include <irrlicht.h>

namespace Game
{
	class GameManager
	{
	public:
		GameManager(irr::IrrlichtDevice* p_device);
		~GameManager();

		void GameTick();
		irr::IEventReceiver* GetEventReceiver();
		irr::video::ITexture* GetCameraTexture();
		void SetCameraHeight(float p_cameraHeight);
		void SetGameLength(float p_gameLength);
		irr::scene::ISceneNode* GetRootSceneNode();
		void DrawCameraTexture();
		irr::core::matrix4 GetCameraProjectionMatrix();
		void BeginScene();
		void EndScene();

	private:
		irr::IrrlichtDevice* m_device;
		irr::scene::ISceneManager* m_sceneManager;
		irr::video::IVideoDriver* m_videoDriver;
		irr::scene::ICameraSceneNode* m_camera;

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