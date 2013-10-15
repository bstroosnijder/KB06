#ifndef __GAME__TOWER__H__
#define __GAME__TOWER__H__

#include "Entity.h"
#include "Creature.h"
#include "Projectile.h"

#include <list>
#include <cmath>

namespace Game
{
	/**
	* @brief	A Tower is a game object that attacks monsters
	* @author	Michel van Os
	* @author	Thomas Gravekamp
	*/
	class Tower : public Entity
	{
	public:
		/**
		 * @brief Initialize Tower
		 * @param p_sceneManager Used to register the scenenode to the scenemanager.
		 * @param p_position Position to place this tower.
		 */
		Tower(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df p_position);
		
		void Update(float);

		void SetShootingSpeed(double);
		void SetRange(double);

		double GetHealthPoints();
		double GetShootingSpeed();
		double GetRange();

		void ShootAtNearestCreature(std::list<Creature*>&);
		
	private:
		double m_shootingSpeed;
		double m_range;

		Creature* m_target;
		irr::scene::ISceneNode* m_jointCrystal;

		Creature* SearchNearestCreature(std::list<Creature*>& p_creatureList);
		void ShootProjectileAtCreature(Creature* p_creature);
	};
}

#endif