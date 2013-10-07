#ifndef __GAME__CREATURE__H__
#define __GAME__CREATURE__H__

#include "Entity.h"

namespace Game
{
	/**
	* @brief	Creature class.
	* @author	Thomas Gravekamp
	*/
	class Creature : public Entity
	{
	public:
		Creature(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df p_position);

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