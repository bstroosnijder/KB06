#include "Game/Playground.h"

#include "Game/Tower.h"
#include "Game/Creature.h"
#include "Game/Projectile.h"
#include "Game/Castle.h"
#include "Game/PathBuilder.h"

#include "Utility/Logger.h"

#include <time.h>
#include <Windows.h>

using namespace Game;
using namespace Utility;

Playground::Playground(irr::scene::ISceneManager* p_sceneManager)
{
	m_sceneManager = p_sceneManager;
<<<<<<< HEAD
	m_pathBuilder = new PathBuilder();
	m_path = NULL;
	m_selector = NULL;
	m_pathRouteTemp;

	gameStatus = false;

=======
	gameStatus = false;
>>>>>>> f11f62c1742e416e9e896fd3d066a5ceed8c3059
	Initialize(p_sceneManager);
}

Playground::~Playground()
{
	delete m_pathBuilder;

	m_pathBuilder = NULL;
}

void Playground::Initialize(irr::scene::ISceneManager* p_sceneManager)
{
	m_castle = new Castle(p_sceneManager, irr::core::vector3df());
	m_stargate = new Stargate(p_sceneManager, irr::core::vector3df(0, 0, 1200));

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

<<<<<<< HEAD
	m_pathRouteTemp = (*m_path->m_routes.begin());
	 
=======
	 m_pathRouteTemp = (*m_path->m_routes.begin());
	 

	
>>>>>>> f11f62c1742e416e9e896fd3d066a5ceed8c3059
	//Setup Waves
	atWave = 0;
	for(int i = 0; i<3; ++i)
	{
		waves.push_back(new Game::Wave(p_sceneManager));
	}
<<<<<<< HEAD

	Terrain* terrain = new Terrain();
	m_selector = terrain->GenerateTerrain(p_sceneManager, 10.0);
=======
	
	// Create towers
	tower1 = new Tower(p_sceneManager, irr::core::vector3df(0.0f));
	tower2 = new Tower(p_sceneManager, irr::core::vector3df(100.0f, 0.0f, 0.0f));

	m_towers.push_back(tower1);
	m_towers.push_back(tower2);

	// Create creature
	creature1 = new Creature(p_sceneManager, tower1->GetPosition(), pathRouteTemp);


	Creature* creature2 = new Creature(p_sceneManager, irr::core::vector3df(50.0f, 0.0f, 0.0f), pathRouteTemp);
	creature2->StopFollowing();

	new Castle(p_sceneManager, irr::core::vector3df());

	Terrain* terrain = new Terrain();
	m_selector = terrain->GenerateTerrain(p_sceneManager, 10.0);
	

	m_creatures.push_back(creature1);
	m_creatures.push_back(creature2);
>>>>>>> f11f62c1742e416e9e896fd3d066a5ceed8c3059
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

void Playground::Update(irr::scene::ISceneManager* p_sceneManager, float p_deltaTime)
{
<<<<<<< HEAD
	for(int i = 0; i<m_creatures.size(); ++i)
	{
		irr::core::vector3df position = m_creatures[i]->GetPosition();
		int y = position.Y;
		m_creatures[i]->FollowPath(p_deltaTime);
		position = m_creatures[i]->GetPosition();
		position.Y = y;
		m_creatures[i]->SetPosition(position);
		int x = m_pathRouteTemp->back()->m_point.X - m_creatures[i]->GetPosition().X;
		int z = m_pathRouteTemp->back()->m_point.Z - m_creatures[i]->GetPosition().Z;

=======
	//creature1->FollowPath(p_deltaTime);
	for(int i = 0; i<m_creatures.size(); ++i)
	{
		irr::core::vector3df position = m_creatures[i]->getPosition();
		int y = position.Y;
		m_creatures[i]->FollowPath(p_deltaTime);
		position = m_creatures[i]->getPosition();
		position.Y = y;
		m_creatures[i]->setPosition(position);
		int z = m_pathRouteTemp->back()->m_point.Z - m_creatures[i]->getPosition().Z;
		int x = m_pathRouteTemp->back()->m_point.X - m_creatures[i]->getPosition().X;
>>>>>>> f11f62c1742e416e9e896fd3d066a5ceed8c3059
		if (x < 2 && x>= 0)
		{
			if (z < 2 && z>= 0)
			{
				m_creatures[i]->kill();
				m_creatures.erase(m_creatures.begin()+i);
			}
		}
<<<<<<< HEAD
=======
	}
	// Update creature position
	creature1->FollowPath(p_deltaTime);

	// Update targets
	for (std::list<Tower*>::const_iterator iterator = m_towers.begin(), end = m_towers.end(); iterator != end; ++iterator) {
		(*iterator)->SearchNearestCreature(&m_creatures);

		Projectile* projectile = (*iterator)->ShootAtTarget(p_sceneManager);

		if (projectile != NULL)
		{
			m_projectiles.push_back(projectile);
		}
>>>>>>> f11f62c1742e416e9e896fd3d066a5ceed8c3059
	}


	for (std::list<Projectile*>::const_iterator iterator = m_projectiles.begin(), end = m_projectiles.end(); iterator != end; ++iterator)
	{
		(*iterator)->updatePosition();
	}

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
	
	if (waves.size() != 0)
	{
		if (waves[0]->CheckWaveStatus(&m_creatures))
		{
			waves[0]->SpawnCreature(&m_creatures, m_pathRouteTemp,m_selector);
			
		}
		else
		{
			std::cout << atWave;
			gameStatus = false;
			waves.erase(waves.begin());
		}
	}
}

void Playground::SpawnTower(irr::core::vector2d<irr::s32> p_position)
{
	irr::core::line3d<irr::f32> line = m_sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(p_position,m_sceneManager->getActiveCamera());
	irr::core::vector3df towerPosition;
	irr::core::triangle3df triangle;
	irr::scene::ISceneNode* sceneNodeOut;
	m_sceneManager->getSceneCollisionManager()->getCollisionPoint(line,m_selector, towerPosition,triangle, sceneNodeOut);
	new Tower(m_sceneManager,towerPosition);
	m_sceneManager->getVideoDriver()->draw3DTriangle(triangle,irr::video::SColor(0,255,0,0));
}

void Playground::SellTower(irr::core::vector2d<irr::s32> p_position)
{
	irr::core::line3d<irr::f32> line = m_sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(p_position,m_sceneManager->getActiveCamera());
	irr::core::vector3df towerPosition;
	irr::core::triangle3df triangle;
	irr::scene::ISceneNode* sceneNodeOut;
	m_sceneManager->getSceneCollisionManager()->getCollisionPoint(line,m_selector, towerPosition,triangle, sceneNodeOut);
	sceneNodeOut->drop();
}

void Playground::startNextWave()
{
	if (gameStatus == false)
	{
		if (waves.size() != 0)
		{		
			Game::Wave* wave = waves[0];
			if (wave)
			{
<<<<<<< HEAD
				wave->SpawnWave(m_path->m_pointBegin->m_point);
		
=======
				wave->SpawnWave(tower1->getPosition());
>>>>>>> f11f62c1742e416e9e896fd3d066a5ceed8c3059
				gameStatus = true;				
				++atWave;
			}
		}
	}
}

<<<<<<< HEAD
=======

>>>>>>> f11f62c1742e416e9e896fd3d066a5ceed8c3059
int Playground::returnWaveNumber()
{
	return atWave;
}

int Playground::returnAmountOfCreatures()
{
	return m_creatures.size();

}
