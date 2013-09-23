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
		std::list<PathPoint*> m_pathPoints;
	};
}

#endif