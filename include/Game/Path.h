#ifndef __GAME__PATH__H__
#define __GAME__PATH__H__

#include "PathSegment.h"

#include <list>

namespace Game
{
	class Path
	{
	public:
		Path();
		~Path();

	private:
		std::list<PathSegment*> m_pathSegments;
		PathSegment* m_pathSegmentStart;
		PathSegment* m_pathSegmentEnd;
	};
}

#endif