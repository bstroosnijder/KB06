#ifndef __GAME__GAMEMANAGER__H__
#define __GAME__GAMEMANAGER__H__

#include "Playground.h"
#include "DeltaTimer.h"

#include <irrlicht.h>

namespace Game
{
	class GameManager
	{
	public:
		GameManager(irr::IrrlichtDevice*);
		~GameManager();

		void Update();
		void Render();

	private:
		irr::IrrlichtDevice* m_device;

		Game::DeltaTimer* m_deltaTimer;
		Game::Playground* m_playground;
	};
}

#endif