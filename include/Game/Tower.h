#ifndef __GAME__TOWER__H__
#define __GAME__TOWER__H__

#include <list>
#include <cmath>
#include "Entity.h"
#include "Creature.h"
#include "Projectile.h"

namespace Game

{
	/**
	* @brief	A Tower is a game object that attacks monsters
	* @author	Michel van Os
	* @author	Thomas Gravekamp
	*/
	class Tower : public Entity	{
	public:
		Tower(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df p_position);

		Creature* SearchNearestCreature(std::list<Creature*>* p_creatureList);
		Projectile* ShootAtTarget(irr::scene::ISceneManager* p_sceneManager);

		double GetShootingSpeed();
		double GetRange();
		
		void SetShootingSpeed(double p_shootingSpeed);
		void SetRange(double p_range);

	private:
		double m_shootingSpeed;
		double m_range;

		Creature* m_target;
	};
}

#endif