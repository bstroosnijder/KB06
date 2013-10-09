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
	class Tower : public Entity
	{
	public:
		Tower(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df p_position);
		

		virtual void Update(float);
		double GetHealthPoints();
		double GetShootingSpeed();
		double GetRange();

		Creature* SearchNearestCreature(std::list<Creature*>* p_creatureList);
		Projectile* ShootAtTarget(irr::scene::ISceneManager* p_sceneManager);

		Creature* SearchNearestCreature(std::list<Creature*>* p_creatureList);
		Projectile* ShootAtTarget(irr::scene::ISceneManager* p_sceneManager);
		
	private:
		double m_shootingSpeed;
		double m_range;

		Creature* m_target;
		irr::scene::ISceneNode* m_jointCrystal;
	};
}

#endif