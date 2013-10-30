#ifndef __GAME__PROJECTILE__H__
#define __GAME__PROJECTILE__H__

#include "Creature.h"

namespace Game
{
	/**
	 * @brief	Projectile class.
	 * @author	Thomas Gravekamp
	 * @author	Michel van Os.
	 */
	class Projectile : public Entity
	{
	public:

	   /**
		* @brief	Constructs a projectile object.
		* @param	p_sceneManger The scenemanager.
		* @param	p_playgroundListener The playgroundlistener.
		* @param	p_position The position of this projectile.
		*/
		Projectile(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* p_playgroundListener,
				irr::core::vector3df p_position);

		/**
		 * @brief	Moves the Projectile towards the target Creature.
		 * @param	p_deltaTime	The delta time used for the movement.
		 */
		void MoveTowardsTarget(float p_deltaTime);

		/**
		 * @brief	Returns the movement speed.
		 * @return	float The movement speed.
		 */
		float GetMovementSpeed();

		/**
		 * @brief	Returns the damage.
		 * @return	float The damage.
		 */
		float GetDamage();

		/**
		 * @brief	Returns the target Creature.
		 * @return	Game::Creature* The target creature.
		 */
		Game::Creature* GetTarget();
		
		/**
		 * @brief	Sets the movement speed.
		 * @param	p_movementSpeed The new movement speed.
		 */
		void SetMovementSpeed(float p_movementSpeed);
		
		/**
		 * @brief	Sets the damage.
		 * @param	p_damage The new damage.
		 */
		void SetDamage(float p_damage);
		
		/**
		 * @brief	Sets the Creature target.
		 * @param	p_creature The new Creature target.
		 */
		void SetTarget(Game::Creature* p_creature);

	private:
		
		/**
		 * @brief	The target Creature.
		 */
		Game::Creature* m_target;
		
		/**
		 * @brief	The movement speed.
		 */
		float m_movementSpeed;
		
		/**
		 * @brief	The damage.
		 */
		float m_damage;
	};
}

#endif