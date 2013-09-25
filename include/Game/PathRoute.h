#ifndef __GAME__PATHROUTE__H__
#define __GAME__PATHROUTE__H__

#include <list>
#include "PathPoint.h"

namespace Game
{
	/**
	* @brief	A PathRoute is a list of PathPoint(s)
	*
	*	A PathRoute is determined from a Path and consist of a sequence of PathPoints. 
	*	Monster(s) will use a PathRoute.
	*/
	struct PathRoute
	{
	public:
		std::list<PathPoint*> m_routePoints;

	};
}

#endif