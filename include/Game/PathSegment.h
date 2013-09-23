#ifndef __GAME__PATHSEGMENT__H__
#define __GAME__PATHSEGMENT__H__

#include "PathPoint.h"

#include <irrlicht.h>
#include <vector>

namespace Game
{
	/**
	 * @brief	A single segment of a Path
	 *
	 * A Path will be build of one or more PathSegments. Monsters will follow the PathSegments
	 * inside the Path.
	 * @author	Michel van Os
	*/
	struct PathSegment
	{
	public:
		Game::PathPoint* m_point1;
		Game::PathPoint* m_point2;

		PathSegment();
		PathSegment(PathPoint* p_point1, PathPoint* p_point2);
		
		/**
		 * @brief	Calculates the difference in length of a Unit-Sized-PathSegment
		 *			and a PathSegment with a different length.
		 *
		 * Imagine a Unit-Sized-PathSegment with a length of 1 and a PathSegment with 
		 * a length of 2. Then the speed needs to be scaled down by half. So the value: 0.5f
		 * will be returned.
		 * @parm	UnitLength Length of a Unit-Sized-PathSegment
		*/
		float GetSpeedScale(float p_unitLength);		
	};
}

#endif