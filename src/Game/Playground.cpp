#include "Game/Playground.h"

#include "Game/Tower.h"
#include "Game/PathBuilder.h"
#include "Game/Creature.h"

#include "Utility/Logger.h"

#include <time.h>
#include <Windows.h>

using namespace Game;
using namespace Utility;

irr::scene::IMeshSceneNode* cube;

//Changing values
Creature* creature;

Playground::Playground(irr::scene::ISceneManager* p_sceneManager)
{
	m_pathBuilder = new PathBuilder();

	Initialize(p_sceneManager);
}

Playground::~Playground()
{
	delete m_pathBuilder;
}

void Playground::Initialize(irr::scene::ISceneManager* p_sceneManager)
{
	float range = 10.0f;
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
	
	irr::core::vector3df startPoint(50.0f, 0.0f, 0.0f);
	irr::core::vector3df endPoint(50.0f, 0.0f, 150.0f);

	SetupPath(points1, points2, amount, range, startPoint, endPoint);

	new Tower(p_sceneManager, irr::core::vector3df(0.0f));
	//new Tower(p_sceneManager, irr::core::vector3df(100.0f, 0.0f, 0.0f));

	PathRoute* pathRouteTemp = (*m_path->m_routes.begin());

	creature = new Creature(p_sceneManager, irr::core::vector3df(0.0f, 0.0f, 100.0f), pathRouteTemp);
}

bool Playground::SetupPath(
		irr::core::vector3df* p_points1,
		irr::core::vector3df* p_points2,
		int p_amount,
		float p_range,
		irr::core::vector3df p_pointBegin,
		irr::core::vector3df p_pointEnd)
{
	m_path = m_pathBuilder->BuildPath(p_points1, p_points2, p_amount, p_range, p_pointBegin, p_pointEnd);
	
	return true;
}

float delay = 0.0f;

void Playground::Update(float p_deltaTime)
{
	delay += 0.5f;

	//Sleep(delay);
	/*
	Logger* l = Logger::GetInstance();
	std::stringstream ss;
	ss << "- DeltaTime: "
		<< p_deltaTime
		<< "- Delay: "
		<< delay;
	
	l->Log(Logger::LOG_MESSAGE, ss.str().c_str());
	*/
	creature->FollowPath(p_deltaTime);
}

void Playground::Render(irr::scene::ISceneManager* p_sceneManager)
{
	irr::video::IVideoDriver* videoDriver = p_sceneManager->getVideoDriver();

	std::list<PathPoint*>::iterator front = m_path->m_pathPoints->begin();
	std::list<PathPoint*>::iterator last = m_path->m_pathPoints->end();
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