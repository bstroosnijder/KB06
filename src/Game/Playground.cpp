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

irr::scene::IMeshSceneNode* cube;

Tower* tower1;
Tower* tower2;
Creature* creature1;
Projectile* projectile1;

Playground::Playground(irr::scene::ISceneManager* p_sceneManager)
{
	m_pathBuilder = new PathBuilder();
	m_sceneManager = p_sceneManager;
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

	 m_pathRouteTemp = (*m_path->m_routes.begin());

	
	//Setup Waves
	atWave = 0;
	for(int i = 0; i<3; ++i)
	{
		waves.push_back(new Game::Wave(p_sceneManager));
	}
	
	// Create towers
	tower1 = new Tower(p_sceneManager, irr::core::vector3df(0.0f));
	tower2 = new Tower(p_sceneManager, irr::core::vector3df(100.0f, 100.0f, 100.0f));

	// Create creature
	creature1 = new Creature(p_sceneManager, tower1->getPosition(), m_pathRouteTemp);

	projectile1 = new Projectile(p_sceneManager, tower1->getPosition());

	new Castle(p_sceneManager, irr::core::vector3df());

	projectile1->setFrom(tower1);
	projectile1->setTo(tower2);

	generateTerrain();
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
	creature1->FollowPath(p_deltaTime);
	for(int i = 0; i<m_creatures.size(); ++i)
	{
		m_creatures[i]->FollowPath(p_deltaTime);
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
	if (atWave-1 != -1)
	{
		waves[atWave-1]->SpawnCreature(&m_creatures, m_pathRouteTemp);
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
	Game::Wave* wave = waves[atWave];
	if (wave)
	{
		wave->SpawnWave(tower1->getPosition());

		if (atWave != 3-1)
		{
			++atWave;
		}

	}	
}

void Playground::generateTerrain()
{

	irr::video::IVideoDriver* driver = m_sceneManager->getVideoDriver();
	irr::scene::ITerrainSceneNode* terrain = m_sceneManager->addTerrainSceneNode(
		"resources/terrain-heightmap.bmp",
		0,                  // parent node
		-1,                 // node id
		irr::core::vector3df(0.f, 0.f, 0.f),     // position
		irr::core::vector3df(0.f, 0.f, 0.f),     // rotation
		irr::core::vector3df(2.f, 0.22f, 2.f),  // scale
		irr::video::SColor ( 255, 255, 255, 255 ),   // vertexColor
		5,                  // maxLOD
		irr::scene::ETPS_17,             // patchSize
		4                   // smoothFactor
		);

	terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	terrain->setMaterialTexture(0,
		driver->getTexture("resources/terrain-texture.jpg"));
	terrain->setMaterialTexture(1,
		driver->getTexture("resources/detailmap3.jpg"));

	terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);

	terrain->scaleTexture(1.0f, 20.0f);


	// create triangle selector for the terrain	 
	m_selector = m_sceneManager->createTerrainTriangleSelector(terrain, 0);
	terrain->setTriangleSelector(m_selector);

	// create collision response animator and attach it to the camera
	irr::scene::ISceneNodeAnimator* anim = m_sceneManager->createCollisionResponseAnimator(
		m_selector, m_sceneManager->getActiveCamera(), irr::core::vector3df(60,100,60),
		irr::core::vector3df(0,0,0),
		irr::core::vector3df(0,50,0));
	m_selector->drop();
	irr::scene::ICameraSceneNode* camera = m_sceneManager->getActiveCamera();
	camera->addAnimator(anim);
	anim->drop();
}