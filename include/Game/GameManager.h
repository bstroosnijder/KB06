#ifndef __GAME__GAMEMANAGER__H__
#define __GAME__GAMEMANAGER__H__

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