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
		
		virtual void Update(float);
		void MoveTowardsTarget(float p_deltaTime);

		double GetMovementSpeed();
		double GetDamage();
		Game::Creature* GetTarget();

		void SetMovementSpeed(double p_movementSpeed);
		void SetDamage(double p_damage);
		void SetTarget(Game::Creature* p_creature);

	private:
		Game::Creature* m_target;

		double m_movementSpeed;
		double m_damage;
	};
}

#endif