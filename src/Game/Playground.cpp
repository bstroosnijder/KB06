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
	m_pathBuilder = new PathBuilder();
	m_path = NULL;
	m_selector = NULL;
	
	m_gameStatus = GameStatus::BUILD_PHASE;
	m_playerHealth = 100;
	
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

	m_paths = m_path->m_routes;
	m_pathNumber = m_paths.begin();
	//Setup Waves
	m_waveNumber = 0;
	for(int i = 0; i<3; ++i)
	{
		waves.push_back(new Game::Wave(p_sceneManager));
	}
	
	Terrain* terrain = new Terrain();
	m_selector = terrain->GenerateTerrain(p_sceneManager, 10.0);
	
	// Create towers
	m_towers.push_back(new Tower(p_sceneManager, irr::core::vector3df(0.0f)));
	m_towers.push_back(new Tower(p_sceneManager, irr::core::vector3df(100.0f, 0.0f, 0.0f)));

	// Create creature
	creature1 = new Creature(p_sceneManager, irr::core::vector3df(), *m_pathNumber, m_selector);

	Creature* creature2 = new Creature(p_sceneManager, irr::core::vector3df(50.0f, 0.0f, 0.0f), *m_pathNumber, m_selector);
	creature2->StopFollowing();

	m_creatures.push_back(creature1);
	m_creatures.push_back(creature2);
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

void Playground::Update(float p_deltaTime)
{
	if (m_playerHealth <= 0)
	{
		m_gameStatus = GameStatus::GAME_OVER;
	}
	if (waves.size() == 0)
	{
		m_gameStatus = GameStatus::VICTORY;
	}
	
	std::list<Creature*>::iterator itCreature;
	std::list<Creature*>::iterator itCreatureEnd = m_creatures.end();
	Creature* creature;
	itCreature = m_creatures.begin();
	while (itCreature != itCreatureEnd)
	{
		creature = (*itCreature);

		irr::core::vector3df position = creature->GetPosition();
		float y = position.Y;
		creature->FollowPath(p_deltaTime);
		position = creature->GetPosition();
		position.Y = y;
		creature->SetPosition(position);


		Game::PathRoute* pathtemp = *m_paths.begin();
		int z = pathtemp->back()->m_point.Z - creature->GetPosition().Z;
		int x = pathtemp->back()->m_point.X - creature->GetPosition().X;
		++itCreature;
		if (x < 2 && x>= 0)
		{
			if (z < 2 && z>= 0)
			{
				m_playerHealth-=2;
				creature->Kill();
				m_creatures.remove(creature);
				delete creature;
			}
		}
	}

	//Update targets
	std::list<Tower*>::iterator itTower;
	std::list<Tower*>::iterator itTowerEnd = m_towers.end();
	Tower* tower;
	for (itTower = m_towers.begin(); itTower != itTowerEnd; ++itTower)
	{
		tower = (*itTower);
		tower->SearchNearestCreature(&m_creatures);

		Projectile* projectile = tower->ShootAtTarget(m_sceneManager);

		if (projectile != NULL)
		{
			m_projectiles.push_back(projectile);
		}
	}

	for (std::list<Projectile*>::const_iterator iterator = m_projectiles.begin(), end = m_projectiles.end(); iterator != end; ++iterator)
	{
		(*iterator)->updatePosition();
	}
}

void Playground::Render()
{
	irr::video::IVideoDriver* videoDriver = m_sceneManager->getVideoDriver();

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
		if (waves[0]->CheckWaveStatus(m_creatures))
		{
			if (*m_pathNumber == m_paths.back())
			{
				m_pathNumber = m_paths.begin();
			}
			std::advance(m_pathNumber,1);
			waves[0]->SpawnCreature(m_creatures, *m_pathNumber,m_selector);

		}
		else
		{
			std::cout << m_waveNumber;
			m_gameStatus = GameStatus::BUILD_PHASE;
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
	m_towers.push_back(new Tower(m_sceneManager,towerPosition));
	
}

void Playground::SellTower(irr::core::vector2d<irr::s32> p_position)
{
	irr::scene::ISceneNode* sceneNodeOut;
	sceneNodeOut = m_sceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(p_position);

	std::list<Tower*>::iterator itTower;
	std::list<Tower*>::iterator itTowerEnd = m_towers.end();
	Tower* tower;


	itTower = m_towers.begin();
	while (itTower != itTowerEnd)
	{		
		if (sceneNodeOut  == (*itTower)->GetSceneNode())
		{
			tower = (*itTower);
			
			++itTower;
			sceneNodeOut->remove();
			m_towers.remove(tower);
			return;
		} else
		{
			++itTower;
		}
	}
}

void Playground::startNextWave()
{
	if (m_gameStatus == GameStatus::BUILD_PHASE)
	{
		if (waves.size() != 0)
		{		
			Game::Wave* wave = waves[0];
			if (wave)
			{
				wave->SpawnWave(m_path->m_pointBegin->m_point);
				m_gameStatus = GameStatus::WAVE_SPAWNED;				
				++m_waveNumber;
			}
		}
	}
}


int Playground::GetWaveNumber()
{
	return m_waveNumber;
}

int Playground::GetAmountOfCreatures()
{
	return m_creatures.size();

}

int Playground::GetGameStatus()
{
	return m_gameStatus;
}

int Playground::GetPlayerHealth()
{
	return m_playerHealth;
}
