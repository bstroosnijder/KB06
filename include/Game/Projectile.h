#ifndef __GAME__PROJECTILE__H__
#define __GAME__PROJECTILE__H__

#include "Creature.h"

namespace Game
{
	/**
	* @brief	Projectile.
	* @author	Thomas Gravekamp
	*/
	class Projectile : public Entity
	{
	public:
		Projectile(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* p_playgroundListener,
				irr::core::vector3df p_position);

		/**
		 * @brief	Moves the Projectile towards the target Creature.
		 *
		 * @param	p_deltaTime	The delta time used for the movement.
		 * @author	Michel van Os.
		 */
		void MoveTowardsTarget(float p_deltaTime);

		/**
		 * @brief	Returns the movement speed.
		 * @author	Michel van Os.
		 */
		double GetMovementSpeed();

		/**
		 * @brief	Returns the damage.
		 * @author	Michel van Os.
		 */
		double GetDamage();

		/**
		 * @brief	Returns the target Creature.
		 * @author	Michel van Os.
		 */
		Game::Creature* GetTarget();
		
		/**
		 * @brief	Sets the movement speed.
		 * @param	p_movementSpeed The new movement speed.
		 * @author	Michel van Os.
		 */
		void SetMovementSpeed(double p_movementSpeed);
		
		/**
		 * @brief	Sets the damage.
		 * @param	p_damage The new damage.
		 * @author	Michel van Os.
		 */
		void SetDamage(double p_damage);
		
		/**
		 * @brief	Sets the Creature target.
		 * @param	p_creature The new Creature target.
		 * @author	Michel van Os.
		 */
		void SetTarget(Game::Creature* p_creature);

	private:
		
		/**
		 * @brief	The target Creature.
		 * @author	Michel van Os.
		 */
		Game::Creature* m_target;
		
		/**
		 * @brief	The movement speed.
		 * @author	Michel van Os.
		 */
		double m_movementSpeed;
		
		/**
		 * @brief	The damage.
		 * @author	Michel van Os.
		 */
		double m_damage;
	};
}

#endif