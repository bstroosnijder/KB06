#include "Game/Creature.h"

using namespace Game;

Creature::Creature(irr::scene::ISceneManager* p_sceneManager,
		PlaygroundListener* p_playgroundListener,
		irr::core::vector3df p_position,
		PathRoute* p_pathRoute,
		irr::scene::ITriangleSelector* p_selector)
		:
		PathFollower(p_playgroundListener, p_pathRoute)
{
	m_meshSceneNode = p_sceneManager->addEmptySceneNode();
	irr::scene::ISceneNode* sceneNodeTemp = NULL;

	//Head
	m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk2.7H.x");
	sceneNodeTemp = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
	SetMaterialFlags(sceneNodeTemp);
	
	//Body
	m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk2.7L.x");///testanim1.1.x");
	sceneNodeTemp = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
	SetMaterialFlags(sceneNodeTemp);

	//Left Foot
	m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk2.7LF.x");
	sceneNodeTemp = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
	SetMaterialFlags(sceneNodeTemp);

	//Right Foot
	m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk2.7RF.x");
	sceneNodeTemp = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
	SetMaterialFlags(sceneNodeTemp);

	m_sceneNodeAnimator = p_sceneManager->createCollisionResponseAnimator(
		p_selector, m_meshSceneNode, irr::core::vector3df(10,3,10),
		irr::core::vector3df(0,-10,0),
		irr::core::vector3df(0,0,0)
		);
	m_meshSceneNode->addAnimator(m_sceneNodeAnimator);
	

	m_sceneNodeAnimator->grab();

	m_healthPoints = 100;

	StartFollowing();
}

Creature::~Creature()
{
	m_sceneNodeAnimator->drop();
	m_sceneNodeAnimator = NULL;
}

void Creature::Update(float p_deltaTime)
{		
	irr::core::vector3df position = GetPosition();
	FollowPath(p_deltaTime);
	float y = position.Y;
	position = GetPosition();
	position.Y = y;
	SetPosition(position);

	if (IsEndOfRouteReached())
	{
		m_playgroundListener->CreatureRouteEndReached(this);
	}
}

void Creature::SetHealthPoints(int p_healthPoints)
{
	m_healthPoints = p_healthPoints;
}

int Creature::GetHealthPoints()
{
	return m_healthPoints;
}