#ifndef __GAME__CREATURE__H__
#define __GAME__CREATURE__H__

#include "PathFollower.h"
#include "PathRoute.h"

namespace Game
{
	class Creature : public PathFollower
	{
	public:
		Creature(irr::scene::ISceneManager* p_sceneManager,
			irr::core::vector3df p_position,
			PathRoute* p_pathRoute);

		double getHealthPoints();
		double getMovementSpeed();
		double getDamage();

		void setHealthPoints(double p_healthPoints);
		void setMovementSpeed(double p_movementSpeed);
		void setDamage(double p_damage);

	private:
        double m_healthPoints;
		double m_movementSpeed;
		double m_damage;

	};
}

#endif