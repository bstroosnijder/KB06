#ifndef __GAME__PATH__H__
#define __GAME__PATH__H__

#include "PathSegment.h"

#include <vector>

namespace Game
{
	/**
	 * @brief	A Path the Monsters will follow
	 *
	 * A Path used by Monsters has to be build of one or more PathSegments.
	 * @author	Michel van Os
	*/
	struct Path
	{
	public:
		std::list<PathPoint*>* m_pathPoints;
		PathPoint* m_pointBegin;
		PathPoint* m_pointEnd;
		std::list<std::list<PathPoint*>*> m_routes;

		// @Note	The amount of PathSegments are equal to the amount of
		//			Segments in all routes.
		std::list<PathSegment*> m_pathSegments;

		Path();
		~Path();
	};
}

#endif