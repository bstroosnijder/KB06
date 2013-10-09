#include "Game/Tower.h"

using namespace Game;

Tower::Tower(irr::scene::ISceneManager* p_sceneManager,
			 irr::core::vector3df p_position)
{
	m_animatedMesh = p_sceneManager->getMesh("resources/models/tower/LOLturret/lolturret1.2.x");

	irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	m_meshSceneNode = animatedMeshSceneNode;

	if (m_meshSceneNode != NULL)
	{
		m_meshSceneNode->setPosition(p_position);
		m_jointCrystal = animatedMeshSceneNode->getJointNode("shootingbone");
	}

	SetMaterialFlags();
}

void Tower::Update(float p_deltaTime)
{

}

double Tower::GetShootingSpeed()
{
	return m_shootingSpeed;
}

double Tower::GetRange()
{
	return m_range;
}

void Tower::SetShootingSpeed(double p_shootingSpeed)
{
	m_shootingSpeed = p_shootingSpeed;
}

void Tower::SetRange(double p_range)
{
	m_range = p_range;
}