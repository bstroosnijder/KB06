#include "Game/Creature.h"

using namespace Game;

Creature::Creature(irr::scene::ISceneManager* p_sceneManager,
		irr::core::vector3df p_position,
		PathRoute* p_pathRoute,
		irr::scene::ITriangleSelector* p_selector)
		:
		PathFollower(p_pathRoute)
{
	m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/creature.3ds");
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh,0,1);
	m_meshSceneNode->setPosition(p_position);
	m_meshSceneNode->setScale(irr::core::vector3df(10.0, 10.0, 10.0));
	

	irr::scene::ISceneNodeAnimator* anim = p_sceneManager->createCollisionResponseAnimator(
	p_selector, m_meshSceneNode, irr::core::vector3df(10,3,10),
	irr::core::vector3df(0,-10,0),
	irr::core::vector3df(0,0,0));
	m_meshSceneNode->addAnimator(anim);
	anim->drop();

	m_healthPoints = 100;

	SetMaterialFlags();
	StartFollowing();
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

