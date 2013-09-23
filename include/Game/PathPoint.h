#ifndef __GAME__PATHPOINT__H__
#define __GAME__PATHPOINT__H__

#include <irrlicht.h>
#include <list>

namespace Game
{
	struct PathPoint
	{
	public:
		irr::core::vector3df m_point;
		std::list<PathPoint*> m_pointsConnected;

		PathPoint();
		PathPoint(irr::core::vector3df p_point);
	};
}

#endif