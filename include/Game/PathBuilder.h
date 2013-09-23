#ifndef __GAME__PATHBUILDER__H__
#define __GAME__PATHBUILDER__H__

#include "Path.h"
#include "PathSegment.h"

#include <irrlicht.h>

namespace Game
{
	class PathBuilder
	{
	public:
		Path* BuildPath(irr::core::vector3df*, irr::core::vector3df*, int);
	};
}

#endif