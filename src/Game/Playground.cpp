#include "Game/Playground.h"

#include "Game/Tower.h"
#include "Game/PathBuilder.h"

#include <time.h>

using namespace Game;

irr::scene::IMeshSceneNode* cube;
PathSegment* segment;

PathPoint* pointSelected;

Path* path;

//Changing values
irr::core::vector3df pointFrom;
irr::core::vector3df pointTo;
irr::core::vector3df segmentLength;
irr::core::vector3df segmentPosition;
irr::core::vector3df position;
float speedScale;

//Contant values
float unitLength;
float speed;

Playground::Playground(irr::scene::ISceneManager* p_sceneManager)
{
	PathBuilder* pathBuilder = new PathBuilder();
	/*
			x	y	z			x	y	z
	1		50	0	0			50	0	50
	2		48	0	52			25	0	75
	3		52	0	52			75	0	75
	4		25	0	77			48	0	100
	5		75	0	77			52	0	100
	6		50	0	102			50	0	150
	*/


	int amount = 7;
	irr::core::vector3df* points1 = new irr::core::vector3df[amount];
	irr::core::vector3df* points2 = new irr::core::vector3df[amount];

	points1[0].set(50, 0, 0	);	points2[0].set(50, 0, 50);	//1
	points1[1].set(48, 0, 52);	points2[1].set(25, 0, 75);	//2
	points1[2].set(52, 0, 52);	points2[2].set(75, 0, 75);	//3
	points1[3].set(25, 0, 77);	points2[3].set(48, 0, 100);	//4
	points1[4].set(75, 0, 77);	points2[4].set(52, 0, 100);	//5
	points1[5].set(50, 0, 102);	points2[5].set(50, 0, 150);	//6
	points1[6].set(27, 0, 76);	points2[6].set(71, 0, 74);	//7

	float range = 10.0f;
	irr::core::vector3df startPoint(50.0f, 0.0f, 0.0f);
	irr::core::vector3df endPoint(50.0f, 0.0f, 150.0f);
	path = pathBuilder->BuildPath(points1, points2, amount, range, startPoint, endPoint);

	new Tower(p_sceneManager, irr::core::vector3df(0.0f));
	new Tower(p_sceneManager, irr::core::vector3df(100.0f, 0.0f, 0.0f));

	

	/*
	cube = p_sceneManager->addCubeSceneNode(10, NULL, -1,
			position);
*/
	
	pointSelected =  (*path->m_pathPoints->begin());
}

void Playground::SetupPath()
{

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