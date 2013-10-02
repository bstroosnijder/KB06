#include "Game/Projectile.h"

using namespace Game;

Projectile::Projectile(irr::scene::ISceneManager* p_sceneManager,
					   irr::core::vector3df p_position)
{
	irr::video::ITexture* texture = p_sceneManager->getVideoDriver()->getTexture("resources/tower-texture.jpg");
	m_animatedMesh = p_sceneManager->getMesh("resources/projectile.3ds");
	
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	//m_meshSceneNode->setMaterialTexture(0, texture);
	m_meshSceneNode->setPosition(p_position);
	
	irr::core::vector3df scale(10.0, 10.0, 10.0);
	
	m_meshSceneNode->setScale(scale);

	SetMaterialFlags();
}

double Projectile::getMovementSpeed()
{
	return m_movementSpeed;
}

double Projectile::getDamage()
{
	return m_damage;
}

void Projectile::setMovementSpeed(double p_movementSpeed)
{
	m_movementSpeed = p_movementSpeed;
}

void Projectile::setDamage(double p_damage)
{
	m_damage = p_damage;
}
