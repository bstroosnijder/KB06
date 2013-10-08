#ifndef __GAME__CREATURE__H__
#define __GAME__CREATURE__H__

#include "PathFollower.h"
#include "PathRoute.h"

namespace Game
{
	/**
	* @brief	Creature class.
	* @author	Thomas Gravekamp
	*/
	class Creature : public PathFollower
	{
	public:
		Creature(irr::scene::ISceneManager* p_sceneManager,
			irr::core::vector3df p_position,
			PathRoute* p_pathRoute);

		virtual void Update(float);
		void UpdatePosition();

		void SetHealthPoints(int p_healthPoints);
		int GetHealthPoints();

	private:
        int m_healthPoints;
	};
}

#endif