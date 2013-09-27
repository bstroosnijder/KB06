#include "Game/Creature.h"

using namespace Game;

Creature::Creature(irr::scene::ISceneManager* p_sceneManager,
				   irr::core::vector3df p_position)
{
	irr::video::ITexture* texture = p_sceneManager->getVideoDriver()->getTexture("resources/tower-texture.jpg");
	m_animatedMesh = p_sceneManager->getMesh("resourcesa/creeper.3ds");
	
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	//m_meshSceneNode->setMaterialTexture(0, texture);
	m_meshSceneNode->setPosition(p_position);
	
	irr::core::vector3df scale(10.0, 10.0, 10.0);
	
	m_meshSceneNode->setScale(scale);

	SetMaterialFlags();
}

double Creature::getHealthPoints()
{
	return m_healthPoints;
}

double Creature::getMovementSpeed()
{
	return m_movementSpeed;
}

double Creature::getDamage()
{
	return m_damage;
}

void Creature::setHealthPoints(double p_healthPoints)
{
	m_healthPoints = p_healthPoints;
}

void Creature::setMovementSpeed(double p_movementSpeed)
{
	m_movementSpeed = p_movementSpeed;
}

void Creature::setDamage(double p_damage)
{
	m_damage = p_damage;
}