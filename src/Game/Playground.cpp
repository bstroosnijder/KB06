#include "Game/Playground.h"

namespace Game
{
	//ALEX; graag betere variable namen verzinnen en maken. Height 1 en height 2 roepen meer vragen op dat ze beantwoorden
	Playground::Playground(GameListener* p_gameListener, irr::scene::ISceneManager* p_sceneManager)
	{
		m_gameListener = p_gameListener;
		m_sceneManager = p_sceneManager;

		m_pathBuilder = new PathBuilder();
		m_path = NULL;
		m_pointBegin = irr::core::vector3df(50.0f, 0.0f, 20.0f);
		m_pointEnd = irr::core::vector3df(50.0f, 0.0f, 80.0f);

		m_waveNumber = 0;
		m_terrain = NULL;
		m_selector = NULL;
		
		m_castle = new Castle(p_sceneManager, this, irr::core::vector3df(0, 0, 0));
		m_stargate = new Stargate(p_sceneManager, this, irr::core::vector3df(10000, 0, 0));
	
		Initialize(p_sceneManager);
	}

	Playground::~Playground()
	{
		delete m_pathBuilder;
		m_pathBuilder = NULL;

		if (m_path != NULL)
		{
			delete m_path;
			m_path = NULL;
		}

		delete m_castle;
		m_castle = NULL;

		delete m_stargate;
		m_stargate = NULL;
	}

	void Playground::Initialize(irr::scene::ISceneManager* p_sceneManager)
	{
		GenerateWaves();

		int amount = 8;
		irr::core::vector3df* points1 = new irr::core::vector3df[amount];
		irr::core::vector3df* points2 = new irr::core::vector3df[amount];
		
		//The following coordinates are used for testing Paths.
		//modify the amount variable to the amount of points segments in the Path.
		/*
		points1[0].set(50, 0, 0	);	points2[0].set(50, 0, 50);	//1
		points1[1].set(48, 0, 52);	points2[1].set(25, 0, 75);	//2
		points1[2].set(52, 0, 52);	points2[2].set(75, 0, 75);	//3
		points1[3].set(25, 0, 77);	points2[3].set(48, 0, 100);	//4
		points1[4].set(75, 0, 77);	points2[4].set(52, 0, 100);	//5
		points1[5].set(50, 0, 102);	points2[5].set(50, 0, 150);	//6
		points1[6].set(27, 0, 76);	points2[6].set(71, 0, 74);	//7
		*/
		/*
		points1[0].set(500, 0, 0);		points2[0].set(250, 0, 500);	//2
		points1[1].set(500, 0, 0);		points2[1].set(750, 0, 500);	//3
		points1[2].set(250, 0, 500);	points2[2].set(750, 0, 500);	//4
		points1[3].set(250, 0, 500);	points2[3].set(250, 0, 1000);	//5
		points1[4].set(750, 0, 500);	points2[4].set(750, 0, 1000);	//6
		points1[5].set(250, 0, 1000);	points2[5].set(750, 0, 1000);	//7
		points1[6].set(250, 0, 1000);	points2[6].set(500, 0, 1500); //8
		points1[7].set(750, 0, 1000);	points2[7].set(500, 0, 1500); //9

		SetupPath(points1, points2, amount, 20.0f, m_pointBegin, m_pointEnd);
		m_pathRouteSelected = m_path->m_routes.begin();
		CreatePathPointMarkers();
		ConnectPathToStargateAndCastle();
		*/

		m_terrain = new Terrain();
		m_selector = m_terrain->GenerateTerrain(p_sceneManager, 10.0);
		m_gameDimensions.Height = m_terrain->GetTerrainDimensions().Height;
	}

	bool Playground::SetupPath(
			irr::core::vector3df* p_points1,
			irr::core::vector3df* p_points2,
			int p_amount)
	{
		if (p_points1 == NULL || p_points2 == NULL || p_amount <= 0)
		{
			m_isPathValid = false;
			return false;
		}

		Path* pathNew = NULL;

		PathPoint* pointBegin1 = new PathPoint(m_stargate->GetPosition());
		PathPoint* pointBegin2 = new PathPoint(m_stargate->GetJointBasePosition());
		PathPoint* pointEnd1 = new PathPoint(m_castle->GetJointPathPosition());
		PathPoint* pointEnd2 = new PathPoint(m_castle->GetJointCenterPosition());

		pointBegin1->m_pointsConnected.push_back(pointBegin2);
		pointBegin2->m_pointsConnected.push_back(pointBegin1);

		pointEnd1->m_pointsConnected.push_back(pointEnd2);
		pointEnd2->m_pointsConnected.push_back(pointEnd1);

		PathSegment* segmentBegin = new PathSegment(pointBegin1, pointBegin2);
		PathSegment* segmentEnd = new PathSegment(pointEnd1, pointEnd2);

		pathNew = m_pathBuilder->BuildPath(p_points1, p_points2, p_amount, segmentBegin, segmentEnd);

		if (pathNew != NULL)
		{
			//Check if the Path is valid.
			if (pathNew->m_routes.size() != 0 &&
					pathNew->m_pathSegments.size() != 0 &&
					pathNew->m_pointBegin != NULL &&
					pathNew->m_pointEnd != NULL &&
					pathNew->m_pathPoints->size() >= 2)
			{
				ConnectPathToStargateAndCastle();
				m_isPathValid = true;
				m_path = pathNew;

				CreatePathPointMarkers();
				return true;
			}
			else
			{
				delete pathNew;
				delete segmentBegin;
				delete segmentEnd;
			}
		}
		else
		{
			delete pointBegin1;
			delete pointBegin2;
			delete pointEnd1;
			delete pointEnd2;
			delete segmentBegin;
			delete segmentEnd;
		}

		m_isPathValid = false;
		m_path = NULL;
		return false;
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

	bool Playground::IsPathReady()
	{
		return (m_isPathValid && m_path != NULL);
	}

	void Playground::Update(float p_deltaTime)
	{	
		p_deltaTime *= 5;

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

		//Update Creatures
		std::list<Creature*>::iterator itCreature = m_creatures.begin();
		std::list<Creature*>::iterator itCreatureEnd = m_creatures.end();
		Creature* creature;
		while (itCreature != itCreatureEnd)
		{
			creature = (*itCreature);
			++itCreature;

			creature->FollowPath(p_deltaTime, m_terrain);
			if (creature->GetHealthPoints() <= 0.0)
			{
				OnCreatureDestroyed(creature);
			}
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

		//Update Markers
		std::list<Marker*>::iterator itMarkers = m_markers.begin();
		std::list<Marker*>::iterator itMarkersEnd = m_markers.end();
		while (itMarkers != itMarkersEnd)
		{
			(*itMarkers)->UpdatePosition(p_deltaTime);
			++itMarkers;
		}

		if (m_waves.size() != 0)
		{
			if (m_waves[0]->CheckWaveStatus(m_creatures))
			{
				m_waves[0]->SpawnCreature(m_creatures, *m_pathRouteSelected);
				if (*m_pathRouteSelected == m_path->m_routes.back())
				{
					m_pathRouteSelected = m_path->m_routes.begin();
				}
				else
				{
					std::advance(m_pathRouteSelected, 1);
				}
			}
			else
			{
				std::cout << m_waveNumber;
				m_waves.erase(m_waves.begin());
			}
		}
	}

	void Playground::Render()
	{
		irr::video::IVideoDriver* videoDriver = m_sceneManager->getVideoDriver();

		if (m_path != NULL)
		{
			std::list<PathPoint*>::iterator front = m_path->m_pathPoints->begin();
			std::list<PathPoint*>::iterator last = m_path->m_pathPoints->end();
			std::list<PathPoint*>::iterator it;
			PathPoint* pathPoint;

			std::list<PathPoint*>::iterator front2;
			std::list<PathPoint*>::iterator last2;
			std::list<PathPoint*>::iterator it2;

			irr::core::vector3df start;
			irr::core::vector3df end;
			irr::video::SColor color(255, 255, 0, 0);

			for (it = front; it != last; ++it)
			{
				pathPoint = (*it);

				front2 = pathPoint->m_pointsConnected.begin();
				last2 = pathPoint->m_pointsConnected.end();

				for (it2 = front2; it2 != last2; ++it2)
				{
					PathPoint* pathPoint2 = (*it2);

					start = pathPoint->m_point;
					end = pathPoint2->m_point;

					start /= 10;
					end /= 10;

					videoDriver->draw3DLine(start, end, color);
				}
			}
		}
	}

	bool Playground::CreateTower(irr::core::vector2di p_position)
	{	
		Tower* towerAtPosition = GetTowerAtPosition(p_position);

		if (towerAtPosition != NULL)
		{
			return false;
		}

		irr::scene::ISceneCollisionManager* collisionManager = m_sceneManager->getSceneCollisionManager();
		irr::core::line3d<irr::f32> line = collisionManager->getRayFromScreenCoordinates(p_position, m_sceneManager->getActiveCamera());
		irr::core::vector3df towerPosition;
		irr::core::triangle3df triangle;
		irr::scene::ISceneNode* sceneNodeOut;

		collisionManager->getCollisionPoint(line, m_selector, towerPosition, triangle, sceneNodeOut);
		m_towers.push_back(new Tower(m_sceneManager, this, towerPosition));

		return true;
	}

	bool Playground::DestroyTower(irr::core::vector2di p_position)
	{
		Tower* tower = GetTowerAtPosition(p_position);

		if (tower != NULL)
		{
			m_towers.remove(tower);
			return true;
		}

		return false;
	}

	bool Playground::UpgradeTowerSpeed(irr::core::vector2di p_position)
	{
		Tower* tower = GetTowerAtPosition(p_position);

		if (tower != NULL)
		{
			tower->SetShootingSpeed(tower->GetShootingSpeed()+1);
			return true;
		}

		return false;
	}

	bool Playground::UpgradeTowerRange(irr::core::vector2di p_position)
	{
		Tower* tower = GetTowerAtPosition(p_position);

		if (tower != NULL)
		{
			tower->SetShootingRange(tower->GetShootingRange()+1);
			return true;
		}

		return false;
	}

	bool Playground::UpgradeTowerDamage(irr::core::vector2di p_position)
	{
		Tower* tower = GetTowerAtPosition(p_position);

		if (tower != NULL)
		{
			tower->SetShootingDamage(tower->GetShootingDamage()+1);
			return true;
		}

		return false;
	}

	void Playground::StartNextWave()
	{
		if (m_waves.size() != 0 && m_waveNumber < m_waves.size())
		{		
			Game::Wave* wave = m_waves[m_waveNumber];

			if (wave)
			{
				wave->StartSpawning(m_path->m_pointBegin->m_point);
				++m_waveNumber;
			}
		}
	}

	bool Playground::AreAllWavesFinished()
	{
		return (m_waveNumber >= m_waves.size()-1 ||
				m_waves[m_waveNumber]->CheckWaveStatus(m_creatures) == false);
	}

	int Playground::GetWaveNumber()
	{
		return m_waveNumber;
	}

	int Playground::GetAmountOfCreatures()
	{
		return m_creatures.size();
	}

	int Playground::GetCreaturesSpawned()
	{
		if (m_waveNumber != 0 && m_waveNumber < m_waves.size())
		{
			return m_waves[m_waveNumber]->GetCreaturesSpawned();
		}

		return -1;
	}

	int Playground::GetWaveSize()
	{
		if (m_waveNumber != 0 && m_waveNumber < m_waves.size())
		{
			return m_waves[m_waveNumber]->GetWaveSize();
		}

		return -1;
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

	void Playground::OnCreatureCreated(Creature* p_creature)
	{
		if (p_creature != NULL)
		{
			m_creatures.push_back(p_creature);

			m_gameListener->OnCreatureSpawned();
		}
	}

	void Playground::OnCreatureDestroyed(Creature* p_creature)
	{
		if (p_creature != NULL)
		{
			m_creatures.remove(p_creature);
			delete p_creature;

			m_gameListener->OnCreatureKilled();
		}
	}

	void Playground::OnCreatureHit(Creature* p_creature, Projectile* p_projectile)
	{
		if (p_creature != NULL && p_projectile != NULL)
		{
			p_creature->DecreaseHealthPoints(p_projectile->GetDamage());
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

	float Playground::GetPlaygroundHeight()
	{		
		return m_gameDimensions.Height;
	}

	void Playground::UpdateGameScale(float p_gameLength)
	{
		m_gameDimensions.Width = p_gameLength;
		float oldLength = m_terrain->GetTerrainDimensions().Width;
		float newLength = p_gameLength - 200;

		irr::core::vector3df terrainScaling = irr::core::vector3df(newLength / oldLength, 1.0f, 1.0f);
		
		m_terrain->ScaleTerrain(terrainScaling);
		
		float offset = 50.0f;
		m_castle->SetPositionToJointCenter(irr::core::vector3df(
			-(m_gameDimensions.Width - offset),
			0.0f,
			-(m_gameDimensions.Height / 2)));
		m_stargate->SetPositionToJointBase(irr::core::vector3df(
			-(0.0f + offset),
			0.0f,
			-(m_gameDimensions.Height / 2)));
	}

	void Playground::GenerateWaves()
	{
		m_waves.clear();
		m_waveNumber = 0;

		m_waves.push_back(new Wave(m_sceneManager, this, 10));
		m_waves.push_back(new Wave(m_sceneManager, this, 15));
		m_waves.push_back(new Wave(m_sceneManager, this, 20));
		m_waves.push_back(new Wave(m_sceneManager, this, 25));
		m_waves.push_back(new Wave(m_sceneManager, this, 40));
	}

	Tower* Playground::GetTowerAtPosition(irr::core::vector2di p_position)
	{
		irr::scene::ISceneNode* sceneNode = m_sceneManager->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(p_position);

		std::list<Tower*>::iterator itTower;
		std::list<Tower*>::iterator itTowerEnd = m_towers.end();

		for (itTower = m_towers.begin(); itTower != itTowerEnd; ++itTower)
		{
			if (sceneNode == (*itTower)->GetSceneNode())
			{
				return (*itTower);
			}
		}

		return NULL;
	}

	void Playground::CreatePathPointMarkers()
	{
		if (m_path != NULL)
		{	
			std::list<PathPoint*>::iterator itPathPoint = m_path->m_pathPoints->begin();
			std::list<PathPoint*>::iterator itPathPointEnd = m_path->m_pathPoints->end();
			PathPoint* pathPoint = NULL;
			irr::f32 height;
			Marker* marker = NULL;
			irr::core::vector3df markerPosition;

			while (itPathPoint != itPathPointEnd)
			{
				pathPoint = (*itPathPoint);
				
				markerPosition = pathPoint->m_point;
				markerPosition.Y = 100;

				m_markers.push_back(new Marker(m_sceneManager, this, markerPosition));

				++itPathPoint;
			}
		}
	}

	void Playground::ConnectPathToStargateAndCastle()
	{
		if (m_path != NULL)
		{
			PathPoint* pathPointStargate = new PathPoint(m_stargate->GetJointBase()->getPosition());
			PathPoint* pathPointCastle = new PathPoint(m_castle->GetJointCenter()->getPosition());

			PathPoint* pathPointBeginOld = m_path->m_pointBegin;
			PathPoint* pathPointEndOld = m_path->m_pointEnd;

			//Create new PathSegments
			m_path->m_pathSegments.push_back(new PathSegment(pathPointStargate, m_path->m_pointBegin));
			m_path->m_pathSegments.push_back(new PathSegment(pathPointCastle, m_path->m_pointEnd));

			//Set the new Begin and End PathPoints
			m_path->m_pointBegin = pathPointStargate;
			m_path->m_pointEnd = pathPointCastle;

			//Add the new PathPoints to the list of the Path.
			m_path->m_pathPoints->push_front(pathPointStargate);
			m_path->m_pathPoints->push_back(pathPointCastle);
			
			//Update all PathRoutes with the new PathPoints
			std::list<PathRoute*>::iterator itPathRoute = m_path->m_routes.begin();
			std::list<PathRoute*>::iterator itPathRouteEnd = m_path->m_routes.end();
			PathRoute* pathRoute = NULL;

			while (itPathRoute != itPathRouteEnd)
			{
				pathRoute = (*itPathRoute);

				pathRoute->push_front(pathPointStargate);
				pathRoute->push_back(pathPointCastle);

				itPathRoute ++;
			}
		}
	}
}
