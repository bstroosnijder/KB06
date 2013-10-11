#ifndef __GAME__PLAYGROUND__H__
#define __GAME__PLAYGROUND__H__

#include "Path.h" 
#include "PathBuilder.h"
#include "Tower.h"
#include "Creature.h"
#include "Projectile.h"
#include "PathFollower.h"
#include "Game/Creature.h"
#include "Game/Wave.h"
#include "Game/Terrain.h"
#include <vector>
#include <irrlicht.h>

namespace Game
{
	/**
	* @brief	Playground is an area the game is played on
	*
	*			The playground consist of Tower(s)  Monster(s)  and a Path
	* @author	Michel van Os
	* @author	Menno Postma
	* @author	Thomas Gravekamp
	*/
	class Playground
	{
	public:
		Playground(irr::scene::ISceneManager* p_sceneManager);
		~Playground();

		void Initialize(irr::scene::ISceneManager* p_sceneManager);
		void Update(irr::scene::ISceneManager* p_sceneManager, float p_deltaTime);
		void Render(irr::scene::ISceneManager* p_sceneManager);

		bool SetupPath(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_amount,
				float p_range,
				irr::core::vector3df p_pointBegin,
				irr::core::vector3df p_pointEnd
			);

		void SpawnTower(irr::core::vector2d<irr::s32>);

		void SellTower(irr::core::vector2d<irr::s32>);

		void startNextWave();

		int returnWaveNumber();
		int returnAmountOfCreatures();

	private:
		PathBuilder* m_pathBuilder;
		Path* m_path;
		irr::scene::ISceneManager* m_sceneManager;
		std::vector<Wave*> waves;
		irr::scene::ITriangleSelector* m_selector;
		//std::vector<Creature*> m_creatures; 
		int atWave;
		std::list<Tower*> m_towers;
		std::list<Creature*> m_creatures;
		std::list<Projectile*> m_projectiles;
		std::list<PathFollower*> m_pathFollowers;
		PathRoute* m_pathRouteTemp;
		bool gameStatus;

		float CalculateSpeedScale();
	};
}

#endif