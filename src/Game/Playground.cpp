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
		m_selector = NULL;
	
		Initialize(p_sceneManager);
	}

	Playground::~Playground()
	{
		delete m_pathBuilder;

		m_pathBuilder = NULL;
	}

	void Playground::Initialize(irr::scene::ISceneManager* p_sceneManager)
	{
		m_castle = new Castle(p_sceneManager, this, irr::core::vector3df(0, 0, 0));
		m_stargate = new Stargate(p_sceneManager, this, irr::core::vector3df(0, 0, 0));

		GenerateWaves();

		float range = 10.0f;
		int amount = 8;
		irr::core::vector3df* points1 = new irr::core::vector3df[amount];
		irr::core::vector3df* points2 = new irr::core::vector3df[amount];
		//Alex waarom commentaar
		/*
		points1[0].set(50, 0, 0	);	points2[0].set(50, 0, 50);	//1
		points1[1].set(48, 0, 52);	points2[1].set(25, 0, 75);	//2
		points1[2].set(52, 0, 52);	points2[2].set(75, 0, 75);	//3
		points1[3].set(25, 0, 77);	points2[3].set(48, 0, 100);	//4
		points1[4].set(75, 0, 77);	points2[4].set(52, 0, 100);	//5
		points1[5].set(50, 0, 102);	points2[5].set(50, 0, 150);	//6
		points1[6].set(27, 0, 76);	points2[6].set(71, 0, 74);	//7
		*/
		//# waar staan ze voor
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
	
		m_terrain = new Terrain();
		m_selector = m_terrain->GenerateTerrain(p_sceneManager, 10.0);
		m_gameDimensions.Height = m_terrain->GetTerrainDimensions().Height*10;

		//Setup signs above the path		
		std::list<PathSegment*>::iterator itSegments = m_path->m_pathSegments.begin();
		std::list<PathSegment*>::iterator itSegmentsEnd = m_path->m_pathSegments.end();
		while (itSegments != itSegmentsEnd)
		{	
			//Alex waarom exist1??
			bool exist1 = false;
			//Alex is m_point publiek?
			irr::core::vector3df position1 = (*itSegments)->m_point1->m_point;
			irr::f32 height1 = m_terrain->GetTerrainHeight(position1);
			position1.Y = (height1 + 100);

			bool exist2 = false;
			irr::core::vector3df position2 = (*itSegments)->m_point2->m_point;
			irr::f32 height2 = m_terrain->GetTerrainHeight(position2);
			position2.Y = (height2 + 100);

			std::list<Marker*>::iterator itSigns = m_marker.begin();
			std::list<Marker*>::iterator itSignsEnd = m_marker.end();
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
				//m_marker waarom 2e M caps?
				m_marker.push_back(new Marker(m_sceneManager, this, position1));
			}
			if (!exist2)
			{
				m_marker.push_back(new Marker(m_sceneManager, this, position2));
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
		p_deltaTime *= 5;

		//Update Creatures
		std::list<Creature*>::iterator itCreature = m_creatures.begin();
		std::list<Creature*>::iterator itCreatureEnd = m_creatures.end();
		Creature* creature;
		while (itCreature != itCreatureEnd)
		{
			creature = (*itCreature);
			++itCreature;

			creature->FollowPath(p_deltaTime, m_terrain);
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

		//Update Markers
		std::list<Marker*>::iterator itMarkers = m_marker.begin();
		std::list<Marker*>::iterator itMarkersEnd = m_marker.end();
		while (itMarkers != itMarkersEnd)
		{
			(*itMarkers)->UpdatePosition(p_deltaTime);
			++itMarkers;
		}

		if (m_waves.size() != 0)
		{
			if (m_waves[0]->CheckWaveStatus(m_creatures))
			{
				m_waves[0]->SpawnCreature(m_creatures, *m_pathNumber);
				if (*m_pathNumber == m_path->m_routes.back())
				{
					m_pathNumber = m_path->m_routes.begin();
				}
				else
				{
					std::advance(m_pathNumber, 1);
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
		float oldLength = m_terrain->GetTerrainDimensions().Width * 10;
		float newLength = p_gameLength - 200;

		irr::core::vector3df terrainScaling = irr::core::vector3df(newLength / oldLength, 1.0f, 1.0f);
		
		m_terrain->ScaleTerrain(terrainScaling);
		m_terrain->SetPosition(100);

		m_castle->SetPosition(irr::core::vector3df(m_gameDimensions.Width - 50, 0.0f, m_gameDimensions.Height / 2));
		m_stargate->SetPosition(irr::core::vector3df(50.0f, 0.0f, m_gameDimensions.Height / 2));
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
}
