#ifndef __GAME__PATHPOINT__H__
#define __GAME__PATHPOINT__H__

#include <irrlicht.h>
#include <list>

namespace Game
{
	/**
	* @brief	A PathPoint is a point in 3d space
	*
	*			A pathpoint is connected with other PathPoints to form a Path
	* @author	Michel van Os
	* @author	Menno Postma
	*/
	struct PathPoint
	{
	public:
		irr::core::vector3df m_point;
		std::list<PathPoint*> m_pointsConnected;

		/**
		* @brief	Constructs the path
		*/
		PathPoint(irr::core::vector3df p_point);
	};
}

#endif