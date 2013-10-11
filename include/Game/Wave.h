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
	/**
	 * @brief	This Class creates a collection of creatures and spawns them in certain times on certain places, following certain routes.
	 *			
	 * @author	Bram van Elderen
	 */
	class Wave
	{
	public:
		/**
		* @brief The constructor initializes the object.
		* @param p_scenemanager is used to create creatures in the class
		*/
		Wave(irr::scene::ISceneManager* p_sceneManager);
		~Wave();

		/** 
		* @brief this method initializes the startposition of the creatures and starts the timer of the wave.
		*/
		void SpawnWave(irr::core::vector3df p_startPosition);

		/**
		* @brief This method spawns the creatures onto the map.
		* @param The creatures are added in the p_creatures pointer
		* @param the p_path is used to give the creatures a walking path
		*/
		void SpawnCreature(std::list<Creature*>& p_creatures,PathRoute* p_path, irr::scene::ITriangleSelector* p_selector);

		/**
		* @brief This method checks the status of the wave.
		* @param p_creatures is a vector that is used to check if there are still creatures alive
		*/
		bool CheckWaveStatus(std::list<Creature*>& p_creatures);

	private:
		irr::scene::ISceneManager* m_sceneManager;
		bool m_creaturesSpawned;
		bool m_isActive;
		Game::Timer* m_timer;
		irr::core::vector3df m_startPosition;
		int m_waveSize;
	};
}
#endif