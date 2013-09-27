#ifndef __GAME__PROJECTILE__H__
#define __GAME__PROJECTILE__H__

#include "Entity.h"

namespace Game
{
	class Projectile : public Entity
	{
	public:
		Projectile(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df p_position);

		double getMovementSpeed();
		double getDamage();

		void setMovementSpeed(double p_movementSpeed);
		void setDamage(double p_damage);

	private:
		double m_movementSpeed;
		double m_damage;

	};
}

#endif