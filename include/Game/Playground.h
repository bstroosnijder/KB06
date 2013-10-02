#ifndef __GAME__PLAYGROUND__H__
#define __GAME__PLAYGORUND__H__

#include "Game/Path.h" 

#include <irrlicht.h>

namespace Game
{
	/**
	* @brief	Playground is an area the game is played on
	*
	*			The playground consist of Tower(s)  Monster(s)  and a Path
	* @author	Michel van Os
	* @author	Menno Postma
	*/
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