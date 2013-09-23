#ifndef __GAME__PLAYGROUND__H__
#define __GAME__PLAYGORUND__H__

#include "Game/Path.h" 

#include <irrlicht.h>

namespace Game
{
	class Playground
	{
	public:
		Playground(irr::scene::ISceneManager*);

		void Render(irr::scene::ISceneManager*);

	private:
		Path* m_path;

		void SetupPath();
		float CalculateSpeedScale();
	};
}

#endif