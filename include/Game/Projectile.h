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
		Projectile(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df p_position);

		void updatePosition();


		double getMovementSpeed();
		double getDamage();
		Game::Entity* getFrom();
		Game::Entity* getTo();



		void setMovementSpeed(double p_movementSpeed);
		void setDamage(double p_damage);
		void setFrom(Game::Entity* p_from);
		void setTo(Game::Entity* p_to);


	private:
		double m_movementSpeed;
		double m_damage;

		Game::Entity* m_from;
		Game::Entity* m_to;

	};
}

#endif