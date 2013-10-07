#ifndef __GAME__CREATURE__H__
#define __GAME__CREATURE__H__

#include "PathFollower.h"
#include "PathRoute.h"

namespace Game
{
<<<<<<< HEAD
	/**
	* @brief	Creature class.
	* @author	Thomas Gravekamp
	*/
	class Creature : public Entity
=======
	class Creature : public PathFollower
>>>>>>> aa1056c071da2b56e6ed3046a022ae59c3ecf056
	{
	public:
		Creature(irr::scene::ISceneManager* p_sceneManager,
			irr::core::vector3df p_position,
			PathRoute* p_pathRoute);

		void updatePosition();

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