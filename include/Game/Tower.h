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
	 * @brief	A Tower is a game object that attacks Creatures.
	 *
	 * @author	Michel van Os
	 * @author	Thomas Gravekamp
	 */
	class Tower : public Entity
	{
	public:
		Tower(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df p_position);

		/**
		 * @brief	Sets the shooting speed.
		 * @param	p_shootingSpeed	The new shooting speed.
		 * @author	Michel van Os.
		 */
		void SetShootingSpeed(double p_shootingSpeed);

		/**
		 * @brief	Sets the shooting range.
		 * @param	p_shootingRange	The new shooting range.
		 * @author	Michel van Os.
		 */
		void SetRange(double p_shootingRange);
		
		/**
		 * @brief	Returns the shooting speed.
		 * @author	Michel van os
		 */
		double GetShootingSpeed();
		
		/**
		 * @brief	Returns the shooting range.
		 * @author	Michel van Os
		 */
		double GetRange();
		
		/**
		 * @brief	Fires a Projetile towards a Creature
		 *
		 *			First the Creature closest to the Tower
		 *			within the shooting will be searched.
		 *			Second a Projectile will be created with
		 *			it's target set to the selected Creature.
		 * @author	Michel van Os
		 */
		void ShootAtNearestCreature(std::list<Creature*>&);
		
	private:
		double m_shootingSpeed;
		double m_shootingRange;

		Creature* m_target;
		irr::scene::ISceneNode* m_jointCrystal;

		Creature* SearchNearestCreature(std::list<Creature*>& p_creatureList);
		void ShootProjectileAtCreature(Creature* p_creature);
	};
}

#endif