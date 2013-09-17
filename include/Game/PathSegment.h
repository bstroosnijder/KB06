#ifndef __GAME__PATHSEGMENT__H__
#define __GAME__PATHSEGMENT__H__

#include <irrlicht.h>

namespace Game
{
	struct PathSegment
	{
	public:
		PathSegment** m_pathSegmentsNext;
		int m_pathSegmentsNextCount;

		irr::core::vector2df m_point1;
		irr::core::vector2df m_point2;
	};
}

#endif