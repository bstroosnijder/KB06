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
		 * @brief	Construct a new tower object.
		 * @param	p_sceneManager The irr::scene::ISceneManager used to store the SceneNode.
		 * @param	p_playgroundListener The PlaygroundListener to handle events.
		 * @param	p_position The position of the Tower
		 */
		Tower(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* m_playgroundListener,
				irr::core::vector3df p_position);

		~Tower();

		/**
		 * @brief	Sets the shooting speed.
		 *
		 * @param	p_shootingSpeed	The new shooting speed.
		 */
		void SetShootingSpeed(float p_shootingSpeed);

		/**
		 * @brief	Sets the shooting range.
		 *
		 * @param	p_shootingRange	The new shooting range.
		 */
		void SetShootingRange(float p_shootingRange);

		/**
		 * @brief	Sets the shooting damage.
		 * @param	p_shootingDamage The new shooting damage.
		 */
		void SetShootingDamage(float p_shootingDamage);
		
		/**
		 * @brief	Returns the shooting speed.
		 * @return	float The shooting speed.
		 */
		float GetShootingSpeed();
		
		/**
		 * @brief	Returns the shooting range.
		 * @return	float The shooting range.
		 */
		float GetShootingRange();

		/**
		 * @brief	Returns the shooting damage.
		 * @return	float The shooting damage.
		 */
		float GetShootingDamage();
		
		/**
		 * @brief	Fires a Projetile at a Creature.
		 *			Searches the list for the closest creature. After that it creates a projectile with that creature as its target.
		 * @param std::list<Creature*>& List of creatures to search in and shoot at.
		 */
		void ShootAtNearestCreature(std::list<Creature*>&);
		
	private:
		float m_shootingSpeed;
		float m_shootingRange;
		float m_shootingDamage;

		irr::scene::ISceneNode* m_jointCrystal;

		Timer* m_timer;

		/**
		 * @brief	Searches for the Creature closest to the Tower.
		 * @param	p_creatureList The list contains the Creatures to search for.
		 * @return	Creature* The Creature that is closest to the Tower.
		 */
		Creature* SearchNearestCreature(std::list<Creature*>& p_creatureList);

		/**
		 * @brief	Creates a Projectile and sets the target to the Creature.
		 * @param	p_creature The Creature target for the Projectile.
		 */
		void ShootProjectileAtCreature(Creature* p_creature);
	};
}

#endif