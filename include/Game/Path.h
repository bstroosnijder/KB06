#ifndef __GAME__PATH__H__
#define __GAME__PATH__H__

#include "PathPoint.h"
#include "PathSegment.h"
#include "PathRoute.h"

#include <vector>

namespace Game
{
	/**
	 * @brief	A Path that may contain multiple PathRoutes.
	 *
	 *			The PathRoutes inside a Path may be used by a Creature. 
	 *			PathSegments are used to create 1-direction segments inside the Path.
	 * @author	Michel van Os
	*/
	struct Path
	{
	public:
		std::list<PathPoint*>* m_pathPoints;
		PathPoint* m_pointBegin;
		PathPoint* m_pointEnd;
		std::list<PathRoute*> m_routes;
		std::list<PathSegment*> m_pathSegments;

		Path();
		~Path();
	};
}

#endif