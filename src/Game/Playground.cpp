#include "Game/Playground.h"

#include "Game/Tower.h"
#include "Game/PathBuilder.h"

#include <time.h>

using namespace Game;

irr::scene::IMeshSceneNode* cube;

//Changing values
Path* path;
std::list<PathPoint*>* pathRoute;
std::list<PathPoint*>::iterator pathRouteCurrentIt;
std::list<PathPoint*>::iterator pathRouteNextIt;
PathPoint* pointCurrent;
PathPoint* pointNext;
irr::core::vector3df segmentLength;
irr::core::vector3df segmentPosition;
irr::core::vector3df cubePosition;
float speedScale;

//Contant values
float unitLength;
float speed;

Playground::Playground(irr::scene::ISceneManager* p_sceneManager)
{
	PathBuilder* pathBuilder = new PathBuilder();

	int amount = 8;
	irr::core::vector3df* points1 = new irr::core::vector3df[amount];
	irr::core::vector3df* points2 = new irr::core::vector3df[amount];
	/*
	points1[0].set(50, 0, 0	);	points2[0].set(50, 0, 50);	//1
	points1[1].set(48, 0, 52);	points2[1].set(25, 0, 75);	//2
	points1[2].set(52, 0, 52);	points2[2].set(75, 0, 75);	//3
	points1[3].set(25, 0, 77);	points2[3].set(48, 0, 100);	//4
	points1[4].set(75, 0, 77);	points2[4].set(52, 0, 100);	//5
	points1[5].set(50, 0, 102);	points2[5].set(50, 0, 150);	//6
	points1[6].set(27, 0, 76);	points2[6].set(71, 0, 74);	//7
	*/

	points1[0].set(50, 0, 0);	points2[0].set(25, 0, 50);	//2
	points1[1].set(50, 0, 0);	points2[1].set(75, 0, 50);	//3
	points1[2].set(25, 0, 50);	points2[2].set(75, 0, 50);	//4
	points1[3].set(25, 0, 50);	points2[3].set(25, 0, 100);	//5
	points1[4].set(75, 0, 50);	points2[4].set(75, 0, 100);	//6
	points1[5].set(25, 0, 100);	points2[5].set(75, 0, 100);	//7
	points1[6].set(25, 0, 100); points2[6].set(50, 0, 150); //8
	points1[7].set(75, 0, 100); points2[7].set(50, 0, 150); //9

	float range = 10.0f;
	irr::core::vector3df startPoint(50.0f, 0.0f, 0.0f);
	irr::core::vector3df endPoint(50.0f, 0.0f, 150.0f);
	path = pathBuilder->BuildPath(points1, points2, amount, range, startPoint, endPoint);

	new Tower(p_sceneManager, irr::core::vector3df(0.0f));
	new Tower(p_sceneManager, irr::core::vector3df(100.0f, 0.0f, 0.0f));

	//Constant values
	unitLength = 10.0f;
	speed = 0.004f;

	//Changing values
	std::list<std::list<PathPoint*>*>::iterator pathRouteIt = path->m_routes.begin();
	std::advance(pathRouteIt, 3);

	pathRoute = (*pathRouteIt);

	pathRouteCurrentIt = pathRoute->begin();
	pathRouteNextIt = pathRouteCurrentIt;
	std::advance(pathRouteNextIt, 1);

	pointCurrent = (*pathRouteCurrentIt);
	pointNext = (*pathRouteNextIt);
	
	segmentLength = pointNext->m_point - pointCurrent->m_point;
	segmentPosition = irr::core::vector3df(0.0f);
	
	cubePosition = pointCurrent->m_point;
	speedScale = unitLength / pointCurrent->m_point.getDistanceFrom(pointNext->m_point);

	cube = p_sceneManager->addCubeSceneNode(10.0f, NULL, -1, cubePosition);
}

void Playground::SetupPath()
{

}

void UpdateCubePosition()
{
	//If the end of the segment is reached
	if (segmentPosition.X >= 1)
	{
		std::list<PathPoint*>::iterator it = pathRouteNextIt;
		std::list<PathPoint*>::iterator itEnd = pathRoute->end();
		std::advance(it, 1);
		
		//If the end of the route is not reached
		if (it != itEnd)
		{
			std::advance(pathRouteCurrentIt, 1);
			std::advance(pathRouteNextIt, 1);

			pointCurrent = (*pathRouteCurrentIt);
			pointNext = (*pathRouteNextIt);

			segmentLength = pointNext->m_point-pointCurrent->m_point;
			speedScale = unitLength / pointCurrent->m_point.getDistanceFrom(pointNext->m_point);

			segmentPosition = irr::core::vector3df(0.0f);
			cubePosition = pointCurrent->m_point + (segmentLength * segmentPosition);
			cube->setPosition(cubePosition);
		}
	}
	else
	{
		segmentPosition += speedScale * speed;
		cubePosition = pointCurrent->m_point + (segmentLength * segmentPosition);

		cube->setPosition(cubePosition);
	}
}

void Playground::Render(irr::scene::ISceneManager* p_sceneManager)
{
	irr::video::IVideoDriver* videoDriver = p_sceneManager->getVideoDriver();

	std::list<PathPoint*>::iterator front = path->m_pathPoints->begin();
	std::list<PathPoint*>::iterator last = path->m_pathPoints->end();
	std::list<PathPoint*>::iterator it;
	PathPoint* pathPoint;

	for (it = front; it != last; ++it)
	{
		pathPoint = (*it);

		std::list<PathPoint*>::iterator front2 = pathPoint->m_pointsConnected.begin();
		std::list<PathPoint*>::iterator last2 = pathPoint->m_pointsConnected.end();
		std::list<PathPoint*>::iterator it2;

		for (it2 = front2; it2 != last2; ++it2)
		{
			PathPoint* pathPoint2 = (*it2);

			irr::core::vector3df start = pathPoint->m_point;
			irr::core::vector3df end = pathPoint2->m_point;
			irr::video::SColor color(255, 255, 0, 0);

			videoDriver->draw3DLine(start, end, color);
		}
	}

	UpdateCubePosition();
}

/*
Playground::Playground(irr::scene::ISceneManager* p_sceneManager)
{o
	new Tower(p_sceneManager, irr::core::vector3df(0, 0, 0));
	new Tower(p_sceneManager, irr::core::vector3df(100, 0, 0));

	SetupPath();

	segment = m_path->m_pathSegments.at(0);

	//Constant values
	unitLength = 10.0f;
	speed = 0.001f;

	//Changing values
	pointFrom = segment->m_point1;
	pointTo = segment->m_point2;	
	segmentLength = pointTo - pointFrom;
	segmentPosition = irr::core::vector3df(0.0f);
	position = pointFrom;
	speedScale = segment->GetSpeedScale(unitLength);

	cube = p_sceneManager->addCubeSceneNode(10, NULL, -1,
			position);


	PathBuilder* pb = new PathBuilder();

	irr::core::vector3df* points1 = new irr::core::vector2df[3];
	irr::core::vector3df* points2 = new irr::core::vector2df[3];

	points1[0].X = 0;
	points1[0].Y = 10;
	points2[0].X = 10;
	points2[0].Y = 12;

	points1[1].X = 8;
	points1[1].Y = 10;
	points2[1].X = 20;
	points2[1].Y = 22;

	points1[2].X = 22;
	points1[2].Y = 18;
	points2[2].X = 30;
	points2[2].Y = 32;

	pb->BuildPath(points1, points2, 3);
}

void Playground::SetupPath()
{
	PathSegment* pathSegment = NULL;

	m_path = new Path();

	m_path->m_pathSegments.push_back(new PathSegment(irr::core::vector3df(50, 0, 0), irr::core::vector3df(30, 0, 20)));
	m_path->m_pathSegments.push_back(new PathSegment(irr::core::vector3df(30, 0, 20), irr::core::vector3df(200, 0, 40)));
	m_path->m_pathSegments.push_back(new PathSegment(irr::core::vector3df(30, 0, 20), irr::core::vector3df(40, 0, 60)));
	m_path->m_pathSegments.push_back(new PathSegment(irr::core::vector3df(200, 0, 40), irr::core::vector3df(40, 0, 60)));
	m_path->m_pathSegments.push_back(new PathSegment(irr::core::vector3df(40, 0, 60), irr::core::vector3df(50, 0, 80)));
	m_path->m_pathSegments.push_back(new PathSegment(irr::core::vector3df(50, 0, 80), irr::core::vector3df(50, 0, 100)));

	m_path->m_pathSegments.at(0)->m_pathSegmentsNext.push_back(m_path->m_pathSegments.at(1));
	m_path->m_pathSegments.at(0)->m_pathSegmentsNext.push_back(m_path->m_pathSegments.at(2));
	m_path->m_pathSegments.at(1)->m_pathSegmentsNext.push_back(m_path->m_pathSegments.at(3));
	m_path->m_pathSegments.at(3)->m_pathSegmentsNext.push_back(m_path->m_pathSegments.at(4));
	m_path->m_pathSegments.at(2)->m_pathSegmentsNext.push_back(m_path->m_pathSegments.at(4));
	m_path->m_pathSegments.at(4)->m_pathSegmentsNext.push_back(m_path->m_pathSegments.at(5));
}


void Playground::Render(irr::scene::ISceneManager* p_sceneManager)
{
	irr::video::IVideoDriver* videoDriver = p_sceneManager->getVideoDriver();

	for (std::vector<PathSegment*>::iterator it = m_path->m_pathSegments.begin(); it != m_path->m_pathSegments.end(); ++it)
	{		
		videoDriver->draw3DLine((*it)->m_point1, (*it)->m_point2, irr::video::SColor(255, 255, 0, 0));
	}
	
	if (segmentPosition.X >= 1)
	{
		int size = segment->m_pathSegmentsNext.size();

		if (size > 0)
		{
			srand(time(NULL));
			int r = rand() % size;
			int index = floor(r);

			segment = segment->m_pathSegmentsNext.at(index);
			
			//Changing values
			pointFrom = segment->m_point1;
			pointTo = segment->m_point2;
			segmentLength = pointTo - pointFrom;
			speedScale = segment->GetSpeedScale(unitLength);

			segmentPosition -= 1.0f;
			segmentPosition += speedScale * speed;

			position = pointFrom + (segmentLength * segmentPosition);
			cube->setPosition(position);
		}
	}
	else
	{
		segmentPosition += speedScale * speed;
		position = pointFrom + (segmentLength * segmentPosition);

		cube->setPosition(position);
	}
}*/