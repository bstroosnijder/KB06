#include "Game/Tower.h"

using namespace Game;

irr::video::ITexture* texture;

Tower::Tower(irr::scene::ISceneManager* p_sceneManager,
			 irr::core::vector3df p_position)
{
	m_animatedMesh = p_sceneManager->getMesh("resources/models/animtest10.x");

	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	m_meshSceneNode->setPosition(p_position);

	SetMaterialFlags();
}

double Tower::getHealthPoints()
{
	return m_healthPoints;
}

double Tower::getShootingSpeed()
{
	return m_shootingSpeed;
}

double Tower::getRange()
{
	return m_range;
}

void Tower::setHealthPoints(double p_healthPoints)
{
	m_healthPoints = p_healthPoints;
}

void Tower::setShootingSpeed(double p_shootingSpeed)
{
	m_shootingSpeed = p_shootingSpeed;
}

void Tower::setRange(double p_range)
{
	m_range = p_range;
}