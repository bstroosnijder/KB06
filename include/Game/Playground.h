#ifndef __GAME__PLAYGROUND__H__
#define __GAME__PLAYGROUND__H__

#include "GameListener.h"
#include "GameStatus.h"
#include "PlaygroundListener.h"
#include "Path.h" 
#include "PathBuilder.h"
#include "Tower.h"
#include "Creature.h"
#include "Projectile.h"
#include "PathFollower.h"
#include "Creature.h"
#include "Wave.h"
#include "Castle.h"
#include "Stargate.h"
#include "Terrain.h"
#include "Marker.h"
#include "Utility/Logger.h"

#include <vector>
#include <irrlicht.h>
#include <math.h>

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
	class Playground : public PlaygroundListener
	{
	public:
		Playground(GameListener* p_gameListener, irr::scene::ISceneManager* p_sceneManager);
		~Playground();

		void Initialize(irr::scene::ISceneManager* p_sceneManager);
		void Update(float p_deltaTime);

		void Render();

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

		void StartNextWave();

		int GetWaveNumber();
		int GetAmountOfCreatures();
		int GetGameStatus();
		int GetPlayerHealth();
		
		int GetPlayerResources();

		//PlaygroundListenerEvents
		void OnProjectileCreated(Projectile* p_projectile);
		void OnProjectileDestroyed(Projectile* p_projectile);
		void OnCreatureCreated(Creature* p_creature);
		void OnCreatureDestroyed(Creature* p_creature);
		void OnCreatureHit(Creature* p_creature, Projectile* p_projectile);
		void OnCreatureRouteEndReached(Creature* p_creature);

	private:
		GameListener* m_gameListener;
		irr::scene::ISceneManager* m_sceneManager;
		PathBuilder* m_pathBuilder;

		Path* m_path;
		irr::core::vector3df m_pointBegin;
		irr::core::vector3df m_pointEnd;

		irr::scene::ITriangleSelector* m_selector;
		std::list<Creature*> m_creatures;
		std::list<Tower*> m_towers;
		std::list<Projectile*> m_projectiles;
		std::list<PathFollower*> m_pathFollowers;
		std::list<PathRoute*>::iterator m_pathNumber;
		std::list<Marker*> m_Marker;

		std::vector<Wave*> waves;

		Creature* creature1;

		Terrain* m_terrain;

		int m_waveNumber;
		int m_gameStatus;
		int m_playerHealth;
		int m_playerResources;

		Castle* m_castle;
		Stargate* m_stargate;

		float CalculateSpeedScale();
	};
}

#endif