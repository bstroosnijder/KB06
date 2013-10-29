#include "Game/PathBuilder.h" 

namespace Game
{
	Path* PathBuilder::BuildPath(
			irr::core::vector3df* p_points1,
			irr::core::vector3df* p_points2,
			int p_pointsCount,
			float p_range,
			irr::core::vector3df p_pointBegin,
			irr::core::vector3df p_pointEnd)
	{
		if (p_points1 == NULL || p_points2 == NULL || p_pointsCount < 0)
			return NULL;

		Path* path = new Path();

		path->m_pathPoints = CreatePathPoints(p_points1, p_points2, p_pointsCount);
		PathJoinPathPoints(path, p_range);
		PathDetermineBeginAndEndPathPoints(path, p_pointBegin, p_pointEnd, p_range);
	
		PathRoute* pathRoute = new PathRoute();
		BuildRoute(path, pathRoute, path->m_pointBegin);

		return path;
	}

	bool PathBuilder::IsPathDirectionAllowed(Path* p_path, PathPoint* p_pathPoint1, PathPoint* p_pathPoint2)
	{
		if (p_path == NULL || p_pathPoint1 == NULL || p_pathPoint2 == NULL)
		{
			Utility::Logger::GetInstance()->Log(Utility::Logger::LOG_ERROR, "PathBuilder:IsPathDirectionAllowed: Invalid parameters");
			return false;
		}

		std::list<PathSegment*>::iterator it;
		std::list<PathSegment*>::iterator itEnd = p_path->m_pathSegments.end();

		for (it = p_path->m_pathSegments.begin(); it != itEnd; ++it)
		{
			PathSegment* pathSegment = (*it);

			//Check if the direction of pathSegment is different then the direction of p_pathPoint1 and p_pathPoint2
			if (pathSegment->m_point1 == p_pathPoint2 && pathSegment->m_point2 == p_pathPoint1)
			{
				return false;
			}
		}
	
		return true;
	}

	void PathBuilder::AddAllowedPathDirectionsFromRoute(Path* p_path, PathRoute* p_pathRoute)
	{
		PathRoute::iterator it = p_pathRoute->begin();
		int size = p_pathRoute->size();
		PathPoint* pathPoint;
		PathPoint* pathPointNext;
		std::list<PathSegment*>::iterator itPathSegment;
		std::list<PathSegment*>::iterator itEnd = p_path->m_pathSegments.end();
		PathSegment* oldPathSegment;
		bool allreadyExists;

		for (int itIndex = 0; itIndex < size-1; ++itIndex)
		{
			allreadyExists = false;
			pathPoint = (*it);
			++it;
			pathPointNext = (*it);

			//Check for duplicates
			for (itPathSegment = p_path->m_pathSegments.begin(); itPathSegment != itEnd; ++itPathSegment)
			{
				oldPathSegment = (*itPathSegment);

				if (oldPathSegment->m_point1 == pathPoint && oldPathSegment->m_point2 == pathPointNext)
				{
					allreadyExists = true;
				}
			}

			//If there was no duplicate
			if (!allreadyExists)
			{
				p_path->m_pathSegments.push_back(new PathSegment(pathPoint, pathPointNext));
			}
		}
	}
		
	void PathBuilder::BuildRoute(
			Path* p_path,
			PathRoute*& p_pathRoute,
			PathPoint* p_pathPointCurrent)
	{
		if (p_path == NULL || p_pathRoute == NULL || p_pathPointCurrent == NULL)
		{
			Utility::Logger::GetInstance()->Log(Utility::Logger::LOG_ERROR, "PathBuilder:BuildRoute: Invalid parameters");
			return;
		}

		p_pathRoute->push_back(p_pathPointCurrent);

		std::list<PathPoint*>::iterator end = p_pathPointCurrent->m_pointsConnected.end();
		std::list<PathPoint*>::iterator it;

		PathPoint* pathPointIt;
		
		for (it = p_pathPointCurrent->m_pointsConnected.begin(); it != end; ++it)
		{
			pathPointIt = (*it);

			if (IsPathDirectionAllowed(p_path, p_pathPointCurrent, pathPointIt) == false)
			{
				continue;
			}

			if (pathPointIt == p_path->m_pointEnd)
			{
				//End PathPoint found
			
				//Make a new list (pathListNew). And copy all elements in p_listCurrent in the new list
				PathRoute* pathRouteNew = new PathRoute(*p_pathRoute);

				p_pathRoute->push_back(pathPointIt);
				p_path->m_routes.push_back(p_pathRoute);
				AddAllowedPathDirectionsFromRoute(p_path, p_pathRoute);

				//Change the current list pointer to the created list.
				p_pathRoute = pathRouteNew;
			}
			else
			{
				//Check if PathPoint::pathPointIt is already explored in current Path::p_pathRoute
				std::list<PathPoint*>::iterator begin2 = p_pathRoute->begin();
				std::list<PathPoint*>::iterator end2 = p_pathRoute->end();
				std::list<PathPoint*>::iterator it2;
			
				bool alreadyExplored = false;

				for (it2 = begin2; it2 != end2; ++it2)
				{
					PathPoint* pathPointIt2 = (*it2);

					if (pathPointIt2 == pathPointIt)
					{
						alreadyExplored = true;
						break;
					}
				}

				//If not found
				if (alreadyExplored == false)
				{
					BuildRoute(p_path, p_pathRoute, pathPointIt);
				}
			}
		}

		p_pathRoute->pop_back();
	}

	std::list<PathPoint*>* PathBuilder::CreatePathPoints(
			irr::core::vector3df* p_points1,
			irr::core::vector3df* p_points2,
			int p_pointsCount)
	{
		if (p_points1 == NULL || p_points2 == NULL)
		{
			Utility::Logger::GetInstance()->Log(Utility::Logger::LOG_ERROR, "PathBuilder:CreatePathPoints: Invalid parameters");
			return NULL;
		}
		else if (p_pointsCount < 1)
		{
			Utility::Logger::GetInstance()->Log(Utility::Logger::LOG_ERROR, "PathBuilder:CreatePathPoints: Point count is lower then 1");
		}

		std::list<PathPoint*>* pathPoints = new std::list<PathPoint*>();
		PathPoint* point1;
		PathPoint* point2;
	
		for (int pointIndex = 0; pointIndex < p_pointsCount; ++pointIndex)
		{
			point1 = new PathPoint(p_points1[pointIndex]);
			point2 = new PathPoint(p_points2[pointIndex]);
		
			point1->m_pointsConnected.push_back(point2);
			point2->m_pointsConnected.push_back(point1);

			pathPoints->push_back(point1);
			pathPoints->push_back(point2);
		}

		return pathPoints;
	}

	void PathBuilder::PathJoinPathPoints(Path* p_path, float p_range)
	{
		if (p_path == NULL)
		{
			Utility::Logger::GetInstance()->Log(Utility::Logger::LOG_ERROR, "PathBuilder:PathJoinPathPoints: Invalid parameters");
			return;
		}
		else if (p_range < 0)
		{
			Utility::Logger::GetInstance()->Log(Utility::Logger::LOG_ERROR, "PathBuilder:PathJoinPathPoints: Range is lower then 0");
		}

		std::list<PathPoint*>* points = p_path->m_pathPoints;
	
		std::list<PathPoint*>::iterator itPoint;
		std::list<PathPoint*>::iterator itPointNear;
		std::list<PathPoint*>::iterator itEnd = points->end();
		
		PathPoint* point;
		PathPoint* pointNear;
		PathPoint* pointNearConnected;
		std::vector<PathPoint*> pointsNear;

		for (itPoint = points->begin(); itPoint != itEnd; ++itPoint)
		{
			point = (*itPoint);
			pointsNear.clear();

			for (itPointNear = points->begin(); itPointNear != itEnd; ++itPointNear)
			{
				pointNear = (*itPointNear);
			
				if (pointNear == point)
					continue;
			
				//Check if a PathPoint:pointNear is close to PathPoint:point
				if (point->m_point.getDistanceFrom(pointNear->m_point) < p_range)
				{
					pointsNear.push_back(pointNear);
				}
			}
				
			//If there is atleast 1 PathPoint close to another PathPoint
			if (pointsNear.size() != 0)
			{
				//Start combining the PathPoints
				for (std::vector<PathPoint*>::iterator itPointNear = pointsNear.begin(); itPointNear != pointsNear.end(); ++itPointNear)
				{
					pointNear = (*itPointNear);
					pointNearConnected = (*pointNear->m_pointsConnected.begin());

					point->m_point += pointNear->m_point;
					point->m_pointsConnected.push_back(pointNearConnected);

					pointNearConnected->m_pointsConnected.remove(pointNear);
					pointNearConnected->m_pointsConnected.push_back(point);

					points->remove(pointNear);
					delete pointNear;
				}
			
				point->m_point /= static_cast<float>(pointsNear.size()) + 1;
			}
		}
	}

	void PathBuilder::PathDetermineBeginAndEndPathPoints(
			Path* p_path,
			irr::core::vector3df p_pointBegin,
			irr::core::vector3df p_pointEnd,
			float p_range)
	{
		if (p_path == NULL)
		{
			Utility::Logger::GetInstance()->Log(Utility::Logger::LOG_ERROR, "PathBuilder:PathDetermineBeginAndEndPathPoints: Invalid parameters");
		}
		else if (p_range < 0)
		{
			Utility::Logger::GetInstance()->Log(Utility::Logger::LOG_ERROR, "PathBuilder:PathDetermineBeginAndEndPathPoints: Range is lower then 0");
		}

		std::list<PathPoint*>::iterator it;
		std::list<PathPoint*>::iterator itEnd = p_path->m_pathPoints->end();
		PathPoint* pathPointIt;

		for (it = p_path->m_pathPoints->begin(); it != itEnd; ++it)
		{
			pathPointIt = (*it);

			if (pathPointIt->m_point.getDistanceFrom(p_pointBegin) < p_range)
			{
				p_path->m_pointBegin = pathPointIt;
				pathPointIt->m_point = p_pointBegin;
			}
			if (pathPointIt->m_point.getDistanceFrom(p_pointEnd) < p_range)
			{
				p_path->m_pointEnd = pathPointIt;
				pathPointIt->m_point = p_pointEnd;
			}
		}

		//If the begin PathPoint is not connected to the begin.
		//Connect the PathPoint closest to the begin with the begin.
		//Connect the PathPoint closest to the end with the end.
		if (p_path->m_pointBegin == NULL || p_path->m_pointEnd == NULL)
		{
			PathPoint* targetBegin = NULL;
			PathPoint* targetEnd = NULL;
			float targetBeginDistance = -1.0f;
			float targetEndDistance = -1.0f;
			float itBeginDistance = -1.0f;
			float itEndDistance = -1.0f;

			for (it = p_path->m_pathPoints->begin(); it != itEnd; ++it)
			{
				pathPointIt =(*it);
				itBeginDistance = abs(pathPointIt->m_point.Z - p_pointBegin.Z);
				itEndDistance = abs(pathPointIt->m_point.Z - p_pointBegin.Z);

				if (itBeginDistance < targetBeginDistance == -1 )
				{
					targetBeginDistance = itBeginDistance;
					targetBegin = pathPointIt;
				}
				if (itEndDistance < targetEndDistance)
				{
					targetEndDistance = itEndDistance;
					targetEnd = pathPointIt;
				}
			}
		}
	}
}