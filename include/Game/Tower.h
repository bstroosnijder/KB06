#ifndef __GAME__TOWER__H__
#define __GAME__TOWER__H__

#include "Entity.h"

namespace Game
{
	/**
	* @brief	A Tower is a game object that attacks monsters
	* @author	Michel van Os
	* @atuhor	Thomas Gravekamp
	*/
	class Tower : public Entity
	{
	public:
		Tower(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df p_position);
		

		virtual void Update(float);
		double GetHealthPoints();
		double GetShootingSpeed();
		double GetRange();

		void SetShootingSpeed(double p_shootingSpeed);
		void SetRange(double p_range);
		
	private:
		double m_shootingSpeed;
		double m_range;

	};
}

#endif