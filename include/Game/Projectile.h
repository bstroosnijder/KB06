#ifndef __GAME__PROJECTILE__H__
#define __GAME__PROJECTILE__H__

#include "Entity.h"

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
		
		virtual void Update(float p_deltaTime);
		void UpdatePosition(float p_deltaTime);

		double GetMovementSpeed();
		double GetDamage();
		Game::Entity* GetFrom();
		Game::Entity* GetTo();

		void SetMovementSpeed(double p_movementSpeed);
		void SetDamage(double p_damage);
		void SetFrom(Game::Entity* p_from);
		void SetTo(Game::Entity* p_to);

	private:
		double m_movementSpeed;
		double m_damage;

		Game::Entity* m_from;
		Game::Entity* m_to;
	};
}

#endif