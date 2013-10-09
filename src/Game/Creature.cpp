#include "Game/Creature.h"

using namespace Game;

Creature::Creature(irr::scene::ISceneManager* p_sceneManager,
		irr::core::vector3df p_position,
		PathRoute* p_pathRoute)
		:
		PathFollower(p_pathRoute)
{
	//m_animatedMesh = p_sceneManager->getMesh("resources/temp/models/animtest9.x");///creature/goomba/goombawalk1.1.x");
	m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk1.8.x");
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);

	irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	
	m_meshSceneNode = animatedMeshSceneNode;

	m_meshSceneNode->setPosition(p_position);
	
	m_healthPoints = 100;

	SetMaterialFlags();
	StartFollowing();
}

void Creature::Update(float p_deltaTime)
{
	UpdatePosition();
}

void Creature::UpdatePosition()
{
	return;
}
void Creature::SetHealthPoints(int p_healthPoints)
{
	m_healthPoints = p_healthPoints;
}

int Creature::GetHealthPoints()
{
	return m_healthPoints;
}

void Creature::kill()
{
	m_meshSceneNode->remove();
}
