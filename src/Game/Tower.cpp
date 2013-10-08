#include "Game/Tower.h"

using namespace Game;

Tower::Tower(irr::scene::ISceneManager* p_sceneManager,
			 irr::core::vector3df p_position)
{
	m_animatedMesh = p_sceneManager->getMesh("resources/models/tower/tower.3ds");

	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	m_meshSceneNode->setPosition(p_position);

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