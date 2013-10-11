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
			PathRoute* p_pathRoute,
			irr::scene::ITriangleSelector* p_selector);

		~Creature();

		virtual void Update(float);
		void UpdatePosition();

		void SetHealthPoints(int p_healthPoints);
		int GetHealthPoints();
		void Kill();

	private:
        int m_healthPoints;
		irr::scene::ISceneNodeAnimator* m_sceneNodeAnimator;
	};
}

#endif