#ifndef __GAME__TOWER__H__
#define __GAME__TOWER__H__

#include "Entity.h"
#include "Creature.h"
#include "Projectile.h"
#include "Timer.h"
#include "Utility/Logger.h"

#include <list>
#include <cmath>

namespace Game
{
	/**
	 * @brief	A Tower is a game object that attacks Creatures.
	 *
	 * @author	Michel van Os
	 * @author	Thomas Gravekamp
	 * @todo	Add Initialization function.
	 * @todo	Commment private parts.
	 */
	class Tower : public Entity
	{
	public:
		/***
		 * @brief	Creates a Tower.
		 *
		 * @param	p_sceneManager The irr::scene::ISceneManager used to store the SceneNode.
		 * @param	p_playgroundListener the PlaygroundListener to handle events.
		 * @param	p_position The position of the Tower
		 * @author	Michel van Os
		 */
		Tower(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* m_playgroundListener,
				irr::core::vector3df p_position);

		/**
		 * @brief	Sets the shooting speed.
		 *
		 * @param	p_shootingSpeed	The new shooting speed.
		 * @author	Michel van Os.
		 */
		void SetShootingSpeed(float p_shootingSpeed);

		/**
		 * @brief	Sets the shooting range.
		 *
		 * @param	p_shootingRange	The new shooting range.
		 * @author	Michel van Os.
		 */
		void SetShootingRange(float p_shootingRange);

		/**
		 * @brief	Sets the shooting damage.
		 * 
		 * @author	Michel van Os.
		 * @param	p_shootingDamage The new shooting damage.
		 */
		void SetShootingDamage(float p_shootingDamage);
		
		/**
		 * @brief	Returns the shooting speed.
		 *
		 * @author	Michel van Os.
		 */
		float GetShootingSpeed();
		
		/**
		 * @brief	Returns the shooting range.
		 *
		 * @author	Michel van Os.
		 */
		float GetShootingRange();

		/**
		 * @brief	Returns the shooting damage.
		 *
		 * @author	Michel van Os.
		 * @return	The shooting damage.
		 */
		float GetShootingDamage();
		
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
		float m_shootingSpeed;
		float m_shootingRange;
		float m_shootingDamage;

		irr::scene::ISceneNode* m_jointCrystal;

		Timer* m_timer;

		/**
		 * @brief	Searches the Creature closest to the Tower.
		 *
		 * @author	Michel van Os.
		 * @param	p_creatureList The list contains the Creatures to search for.
		 * @return	The Creature that is closest to the Tower.
		 */
		Creature* SearchNearestCreature(std::list<Creature*>& p_creatureList);

		/**
		 * @brief	Creates a Projectile and sets the target to the Creature.
		 *
		 * @author	Michel van Os.
		 * @param	p_creature The Creature target for the Projectile.
		 */
		void ShootProjectileAtCreature(Creature* p_creature);
	};
}

#endif