#include "Game/Playground.h"

namespace Game
{
	Playground::Playground(GameListener* p_gameListener, irr::scene::ISceneManager* p_sceneManager)
	{
		m_gameListener = p_gameListener;
		m_sceneManager = p_sceneManager;
		m_pathBuilder = new PathBuilder();
		m_path = NULL;
		m_selector = NULL;
	
		m_gameStatus = GameStatus::ATTACKER_PLACE_PENCILS;
		m_playerHealth = 100;
		m_playerResources = 1000;
		Initialize(p_sceneManager);
	}

	Playground::~Playground()
	{
		delete m_pathBuilder;

		m_pathBuilder = NULL;
	}

	void Playground::Initialize(irr::scene::ISceneManager* p_sceneManager)
	{
		m_castle = new Castle(p_sceneManager, this, irr::core::vector3df(0, 0, -1200));
		m_stargate = new Stargate(p_sceneManager, this, irr::core::vector3df(0, 0, 1200));

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

		points1[0].set(500, 0, 0);		points2[0].set(250, 0, 500);	//2
		points1[1].set(500, 0, 0);		points2[1].set(750, 0, 500);	//3
		points1[2].set(250, 0, 500);	points2[2].set(750, 0, 500);	//4
		points1[3].set(250, 0, 500);	points2[3].set(250, 0, 1000);	//5
		points1[4].set(750, 0, 500);	points2[4].set(750, 0, 1000);	//6
		points1[5].set(250, 0, 1000);	points2[5].set(750, 0, 1000);	//7
		points1[6].set(250, 0, 1000);	 points2[6].set(500, 0, 1500); //8
		points1[7].set(750, 0, 1000);	points2[7].set(500, 0, 1500); //9
	
		irr::core::vector3df startPoint(500.0f, 0.0f, 0.0f);
		irr::core::vector3df endPoint(500.0f, 0.0f, 1500.0f);

		SetupPath(points1, points2, amount, range, startPoint, endPoint);
		m_pathNumber = m_path->m_routes.begin();
		//Setup Waves
		m_waveNumber = 0;
		for(int i = 0; i<3; ++i)
		{
			waves.push_back(new Game::Wave(p_sceneManager, this));
		}
	
		m_terrain = new Terrain();
		m_selector = m_terrain->GenerateTerrain(p_sceneManager, 10.0);

		//Setup signs above the path		
		std::list<PathSegment*>::iterator itSegments = m_path->m_pathSegments.begin();
		std::list<PathSegment*>::iterator itSegmentsEnd = m_path->m_pathSegments.end();
		while (itSegments != itSegmentsEnd)
		{			
			
			
			bool exist1 = false;
			irr::core::vector3df position1 = (*itSegments)->m_point1->m_point;
			irr::f32 height1 = m_terrain->GetTerrainHeight(position1);
			position1.Y = (height1+100);

			bool exist2 = false;
			irr::core::vector3df position2 = (*itSegments)->m_point2->m_point;
			irr::f32 height2 = m_terrain->GetTerrainHeight(position2);
			position2.Y = (height2+100);



			std::list<Marker*>::iterator itSigns = m_Marker.begin();
			std::list<Marker*>::iterator itSignsEnd = m_Marker.end();
			while (itSigns != itSignsEnd)
			{
				if (position1 == (*itSigns)->GetPosition())
				{
					exist1 = true;
				}
				if (position2 == (*itSigns)->GetPosition())
				{
					exist2 = true;
				}
				++itSigns;
			}
			if (!exist1)
			{
				m_Marker.push_back(new Game::Marker(m_sceneManager,this,position1));
			}
			if (!exist2)
			{
				m_Marker.push_back(new Game::Marker(m_sceneManager,this,position2));
			}			
			++itSegments;			
		}
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
		//p_deltaTime *= 4;

		if (m_playerHealth <= 0)
		{
			m_gameStatus = GameStatus::ATTACKER_VICTORY;
		}
		if (waves.size() == 0)
		{
			m_gameStatus = GameStatus::DEFENDER_VICTORY;
		}
	
		std::list<Creature*>::iterator itCreature = m_creatures.begin();
		std::list<Creature*>::iterator itCreatureEnd = m_creatures.end();
		Creature* creature;
	
		//Update Creatures
		while (itCreature != itCreatureEnd)
		{
			creature = (*itCreature);
			++itCreature;

			creature->FollowPath(p_deltaTime,m_terrain);
		}
	
		//Update Towers
		std::list<Tower*>::iterator itTower = m_towers.begin();
		std::list<Tower*>::iterator itTowerEnd = m_towers.end();
		Tower* tower;

		while (itTower != itTowerEnd)
		{
			tower = (*itTower);
			++itTower;

			tower->ShootAtNearestCreature(m_creatures);
		}
	
		//Update Projectiles
		std::list<Projectile*>::iterator itProjectile = m_projectiles.begin();
		std::list<Projectile*>::iterator itProjectileEnd = m_projectiles.end();
		Projectile* projectile;

		while (itProjectile != itProjectileEnd)
		{
			projectile = (*itProjectile);
			++itProjectile;

			projectile->MoveTowardsTarget(p_deltaTime);
		}

		if (waves.size() != 0)
		{
			if (waves[0]->CheckWaveStatus(m_creatures))
			{
				waves[0]->SpawnCreature(m_creatures, *m_pathNumber);
				if (*m_pathNumber == m_path->m_routes.back())
				{
					m_pathNumber = m_path->m_routes.begin();
				}
				else
				{
					std::advance(m_pathNumber,1);
				}
			}
			else
			{
				std::cout << m_waveNumber;
				m_gameStatus = GameStatus::ATTACKER_PLACE_PENCILS;
				waves.erase(waves.begin());
				m_playerResources += 1000;
			}
		}

		//Update signs (go up and down)
		std::list<Marker*>::iterator itMarkers = m_Marker.begin();
		std::list<Marker*>::iterator itMarkersEnd = m_Marker.end();
		while (itMarkers != itMarkersEnd)
		{
			(*itMarkers)->UpdatePosition(p_deltaTime);
			++itMarkers;
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
	}

	void Playground::SpawnTower(irr::core::vector2d<irr::s32> p_position)
	{	
		if ((m_playerResources - 500 ) >= 0)
		{
			irr::scene::ISceneNode* sceneNodeOut;
			sceneNodeOut = m_sceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(p_position);
		
			std::list<Tower*>::iterator itTower;
			std::list<Tower*>::iterator itTowerEnd = m_towers.end();
			bool towerB = false;
			itTower = m_towers.begin();
			while (itTower != itTowerEnd)
			{		
				if (sceneNodeOut  == (*itTower)->GetSceneNode())
				{
					towerB = true;				
				} 
				++itTower;
			}
		
			if (!towerB)
			{
				m_playerResources -= 500;
				irr::core::line3d<irr::f32> line = m_sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(p_position,m_sceneManager->getActiveCamera());
				irr::core::vector3df towerPosition;
				irr::core::triangle3df triangle;
				irr::scene::ISceneNode* sceneNodeOut;
				m_sceneManager->getSceneCollisionManager()->getCollisionPoint(line,m_selector, towerPosition,triangle, sceneNodeOut);
				m_towers.push_back(new Tower(m_sceneManager, this, towerPosition));
			}
		}	
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
				delete tower;
				m_towers.remove(tower);
				m_playerResources += 250;

				return;
			}
			else
			{
				++itTower;
			}
		}
	}

	void Playground::StartNextWave()
	{
		//if (m_gameStatus == GameStatus::DEFENDER_PLACE_TOWERS)
		{
			if (waves.size() != 0)
			{		
				Game::Wave* wave = waves[0];
				if (wave)
				{
					wave->SpawnWave(m_path->m_pointBegin->m_point);
					m_gameStatus = GameStatus::WAVE_RUNNING;				
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

	int Playground::GetPlayerResources()
	{
		return m_playerResources;
	}

	void Playground::OnProjectileCreated(Projectile* p_projectile)
	{
		if (p_projectile != NULL)
		{
			m_projectiles.push_back(p_projectile);
		}
	}

	void Playground::OnProjectileDestroyed(Projectile* p_projectile)
	{
		if (p_projectile != NULL)
		{
			m_projectiles.remove(p_projectile);
			delete p_projectile;
		}
	}

	void Playground::OnCreatureHit(Creature* p_creature, Projectile* p_projectile)
	{
		if (p_creature != NULL && p_projectile != NULL)
		{

		}
	}

	void Playground::OnCreatureCreated(Creature* p_creature)
	{
		if (p_creature != NULL)
		{
			m_creatures.push_back(p_creature);
		}
	}

	void Playground::OnCreatureDestroyed(Creature* p_creature)
	{
		if (p_creature != NULL)
		{
			m_creatures.remove(p_creature);
			delete p_creature;
		}
	}

	void Playground::OnCreatureRouteEndReached(Creature* p_creature)
	{
		if (p_creature != NULL)
		{
			m_creatures.remove(p_creature);
			delete p_creature;

			m_gameListener->OnCreatureReachedCastle();

			if (m_creatures.size() == 0)
			{
				m_gameListener->OnWaveEnded();
			}
		}
	}
}
