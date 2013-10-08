#ifndef __GAME__WAVE__H__
#define __GAME__WAVE__H__

#include "Game/Creature.h"
#include "Game/Timer.h"
#include <vector>
#include <list>
#include <time.h>
#include <iostream>
namespace Game
{
		
	class Wave
	{
	public:
		
		Wave(irr::scene::ISceneManager* p_sceneManager);
		
		~Wave();

		void SpawnWave(irr::core::vector3df p_startPosition);

		void SpawnCreature(std::vector<Creature*>* p_creatures,PathRoute* p_path);

		bool CheckWaveStatus(std::vector<Creature*>* p_creatures);

	private:
		//std::vector<Game::Creature*> m_creatures;
		irr::scene::ISceneManager* m_sceneManager;
		bool m_creaturesSpawned;
		bool m_isActive;
		Game::timer* m_timer;
		irr::core::vector3df m_startPosition;
		int m_waveSize;


	};
}
#endif