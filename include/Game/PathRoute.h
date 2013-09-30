#ifndef __GAME__PATHROUTE__H__
#define __GAME__PATHROUTE__H__

#include "PathPoint.h"

namespace Game
{
	/**
	 * @brief	Contains PathPoints to form a route.
	 *
	 *			The order of the PathPoints inside a PathRoute determine
	 *			the route the Creatures will follow.
	 *
	 * @author	Michel van Os
	*/
	typedef std::list<PathPoint*> PathRoute;
}

#endif