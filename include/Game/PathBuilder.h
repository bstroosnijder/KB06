#ifndef __GAME__PATHBUILDER__H__
#define __GAME__PATHBUILDER__H__

#include "Path.h"
#include "PathSegment.h"

#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	Korte beschrijving
	 *
	 *			Lange beschrijving
	 * @author	Michel van Os
	 * @author	Menno Postma
	 */
	class PathBuilder
	{
	public:
		/**
		 * @param	p_points1	is een lijst met Vector3df. blablabla.
		 * @param	p_points2 is ook een lijst met Vector3df. blablabla.
		 * @todo	Test 1, 2, 3...
		 * @note	Hello World!
		 */
		Path* BuildPath(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_pointsCount,
				float p_range,
				irr::core::vector3df p_pointBegin,
				irr::core::vector3df p_pointEnd);

	private:
		bool IsPathDirectionAllowed(Path* p_path, PathPoint* p_pathPoint1, PathPoint* p_pathPoint2);
		
		/**
		 * @author	Michel van Os
		 * @todo	De PathSegments worden nu dubbel opgeslagen
		 */
		void AddAllowedPathDirectionsFromRoute(Path* p_path, std::list<PathPoint*>* p_pathRoute);

		void BuildRoute(Path* path, std::list<PathPoint*>*& p_pathRoute, PathPoint* p_pathPointCurrent);

		std::list<PathPoint*>* CreatePathPoints(
				irr::core::vector3df* p_points1,
				irr::core::vector3df* p_points2,
				int p_pointsCount);

		void PathJoinPathPoints(Path* p_path, float p_range);
		void PathDetermineBeginAndEndPathPoints(
				Path* p_path,
				irr::core::vector3df p_pointBegin,
				irr::core::vector3df p_pointEnd,
				float p_range);
	};
}

#endif