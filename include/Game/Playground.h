#ifndef __GAME__PLAYGROUND__H__
#define __GAME__PLAYGROUND__H__

#include "GameListener.h"
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
		void UpdateGameScale(float p_gameLength);

		void Render();

		/**
		 * @todo	SetupPath(,,,,,) moet vervangen worden door deze.
		 * @author	Michel van Os
		 */
		bool SetupPath(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_amount);

		bool SetupPath(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_amount,
				float p_range,
				irr::core::vector3df p_pointBegin,
				irr::core::vector3df p_pointEnd
			);

		/**
		 * @brief	Create a Tower at the given 2d screen coordinates.
		 *
		 *			A Tower can only be created if it doesn't collide with
		 *			Towers, Creatures or the Path.
		 * @author	Michel van Os.
		 * @param	p_positon The screen coordinates.
		 * @return	Returns True if a Tower has been created at the screen coordinates.
		 * @todo	Make sure it can't be created at the position of other entities.
		 */
		bool CreateTower(irr::core::vector2di p_position);

		/**
		 * @brief	Destroy a Tower at the given 2d screen coordinates.
		 *
		 * @author	Michel van Os.
		 * @param	p_positon The screen coordinates.
		 * @return	Returns True if a Tower has been destroyed at the screen coordinates.
		 */
		bool DestroyTower(irr::core::vector2di p_position);

		/**
		 * @brief	Increase the fire rate of the Tower at the given 2d screen coordinates.
		 *
		 * @author	Michel van Os.
		 * @param	p_positon The screen coordinates.
		 * @return	Returns True if a Tower has been found and upgraded at the screen coordinates.
		 */
		bool UpgradeTowerSpeed(irr::core::vector2di p_position);

		/**
		 * @brief	Increase the fire range of the Tower at the given 2d screen coordinates.
		 
		 * @author	Michel van Os.
		 * @param	p_positon The screen coordinates.
		 * @return	Returns True if a Tower has been found and upgraded at the screen coordinates.
		 */
		bool UpgradeTowerRange(irr::core::vector2di p_position);

		/**
		 * @brief	Increase the fire damage of the Tower at the given 2d screen coordinates.
		 *
		 * @author	Michel van Os.
		 * @param	p_positon The screen coordinates.
		 * @return	Returns True if a Tower has been found and upgraded at the screen coordinates.
		 */
		bool UpgradeTowerDamage(irr::core::vector2di p_position);

		/**
		 * @brief	Starts the next Wave.
		 *
		 *			If the Wave has been used in the previous round
		 *			the amount of spawned Creatures will be reset automatically.
		 * @author	Michel van Os.
		 */
		void StartNextWave();

		/**
		 * @brief	Returns whether all Waves are finished.
		 *
		 *			All Creatures for all Waves should have been spawned
		 *			and all Creatures should been killed or reached the castle.
		 * @author	Michel van Os.
		 * @return	Returns true if all Waves are finished.
		 * @todo	Check if the codition works.
		 */
		bool AreAllWavesFinished();

		/**
		 * @brief	Returns the current Wave number.
		 *
		 * @author	Michel van Os.
		 * @return	The current Wave number.
		 */
		int GetWaveNumber();

		/**
		 * @brief	Returns the amount of Creatures currently alive.
		 *
		 * @author	Michel van Os.
		 * @return	The amount of Creatures currently alive.
		 */
		int GetAmountOfCreatures();

		int GetCreaturesSpawned();
		int GetWaveSize();

		float GetPlaygroundHeight();

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
		float m_pointRange;
		irr::core::vector3df m_pointBegin;
		irr::core::vector3df m_pointEnd;

		irr::scene::ITriangleSelector* m_selector;
		std::list<Creature*> m_creatures;
		std::list<Tower*> m_towers;
		std::list<Projectile*> m_projectiles;
		std::list<PathFollower*> m_pathFollowers;
		std::list<PathRoute*>::iterator m_pathRouteSelected;
		std::list<Marker*> m_markers;

		std::vector<Wave*> m_waves;
		int m_waveNumber;

		Terrain* m_terrain;
		irr::core::dimension2d<float> m_gameDimensions;

		Castle* m_castle;
		Stargate* m_stargate;

		float CalculateSpeedScale();

		/**
		 * @brief	Generates Waves with the amount of Creatures to spawn as 
		 *			described in the Game Design Document.
		 *
		 * @author	Michel van Os.
		 */
		void GenerateWaves();

		/**
		 * @brief	Returns the Tower at the given 2d screen coordinates.
		 * @author	Michel van Os.
		 * @param	p_position The 2d coordinates on the screen.
		 * @return	The Tower at the given 2d screen coordinates.
		 *			It return NULL when there's no Tower at the 2d screen coordinates.
		 * @todo	Doesn't work properly? It only finds the Tower when you click at it's center?
		 */
		Tower* GetTowerAtPosition(irr::core::vector2di p_position);

		/**
		 * @brief	Creates Markers at all PathPoints in the Path.
		 *
		 *			For every PathPoint in m_path a Marker will be created.
		 *			The position of the Marker will be the position of the
		 *			PathPoint. But the Y-coordinate will be 100 units above
		 *			the Terrain m_terrain Y-coordinate.
		 * @author	Michel van Os.
		 */
		void CreatePathPointMarkers();

		/**
		 * @brief	Connects the Path with the Startgate and the Castle.
		 *
		 *			Updates the Path with a new begin PathPoint and
		 *			a new end PathPoint. It also creates the new
		 *			PathSegments and updates all PathRoutes.
		 * @author	Michel van Os.
		 */
		void ConnectPathToStargateAndCastle();
	};
}

#endif