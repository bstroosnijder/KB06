#include "PathBuilder.h" 

#include <list>
#include <stack>

using namespace Game;

Path* PathBuilder::BuildPath(irr::core::vector3df* p_points1,
		irr::core::vector3df* p_points2,
		int p_pointsCount)
{
	if (p_points1 == NULL || p_points2 == NULL || p_pointsCount < 0)
		return NULL;

	std::list<PathPoint*> points;
	
	for (int pointIndex = 0; pointIndex < p_pointsCount; ++pointIndex)
	{
		PathPoint* point1 = new PathPoint(p_points1[pointIndex]);
		PathPoint* point2 = new PathPoint(p_points2[pointIndex]);
		
		point1->m_pointsConnected.push_back(point2);
		point2->m_pointsConnected.push_back(point1);

		points.push_back(point1);
		points.push_back(point2);
	}
	
	PathPoint* point;
	PathPoint* pointNear;
	PathPoint* pointNearConnected;
	std::vector<PathPoint*> pointsNear;

	for (std::list<PathPoint*>::iterator itPoint = points.begin(); itPoint != points.end();	++itPoint)
	{
		pointsNear.clear();
		point = (*itPoint);

		for (std::list<PathPoint*>::iterator itPointNear = points.begin(); itPointNear != points.end();	++itPointNear)
		{
			pointNear = (*itPointNear);
			
			if (pointNear == point)
				continue;
			
			//Check if a points of a pencil is close to a point of another pencil
			if (point->m_point.getDistanceFrom(pointNear->m_point) < 10)
			{
				pointsNear.push_back(pointNear);
			}
		}

		
		//If there is atleast 1 points of a pencil close to a point of another pencil
		if (pointsNear.size() != 0)
		{
			//Start combining the points of the different pencils
			for (std::vector<PathPoint*>::iterator itPointNear = pointsNear.begin(); itPointNear != pointsNear.end(); ++itPointNear)
			{
				pointNear = (*itPointNear);
				pointNearConnected = (*pointNear->m_pointsConnected.begin());

				point->m_point += pointNear->m_point;
				point->m_pointsConnected.push_back(pointNearConnected);

				//pointNearConnected->m_pointsConnected.clear();
				pointNearConnected->m_pointsConnected.remove(pointNear);
				pointNearConnected->m_pointsConnected.push_back(point);

				points.remove(pointNear);
				delete pointNear;
			}
			
			point->m_point /= pointsNear.size()+1;
		}
	}

	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

	if (points.size() > 0)
	{
		std::list<std::list<PathPoint*>> pathList;
		std::stack<PathPoint*> stackPoints;

		PathPoint* pointsTarget = points.back();
		PathPoint* pointCurrent = NULL;
		
		stackPoints.push(*points.begin());


		/*
		pathList =
		{
			{1,2,4},
			{1,3,2,4}
		};
		*/
	}




	/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/



	Path* path = new Path();
	path->m_pathPoints = points;

	return path;

	/*
	if (p_points1 != NULL && p_points2 != NULL && p_pointsCount > 0)
	{
		int segmentCurrent = 0;
		int segmentNext;
		PathSegment* pathSegments = new PathSegment[p_pointsCount];
		
		pathSegments[segmentCurrent].m_point1.X = p_points1[segmentCurrent].X;
		pathSegments[segmentCurrent].m_point1.Z = p_points1[segmentCurrent].Y;

		for (segmentCurrent = 0; segmentCurrent < p_pointsCount-1; ++segmentCurrent)
		{
			segmentNext = segmentCurrent+1;

			irr::core::vector2df pointDif = p_points1[segmentNext]-p_points2[segmentCurrent];
			pointDif /= 2;

			pathSegments[segmentCurrent].m_point2.X = p_points2[segmentCurrent].X+pointDif.X;
			pathSegments[segmentCurrent].m_point2.Z = p_points2[segmentCurrent].Y+pointDif.Y;
			
			//segmentCurrent.point2 and segmentNext.point1 are connected
			pathSegments[segmentNext].m_point1 = pathSegments[segmentCurrent].m_point2;
		}

		pathSegments[segmentCurrent].m_point2.X = p_points2[segmentCurrent].X;
		pathSegments[segmentCurrent].m_point2.Z = p_points2[segmentCurrent].Y;
	}
	*/
}