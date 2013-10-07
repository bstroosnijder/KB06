#include "Game/Projectile.h"

using namespace Game;

Projectile::Projectile(irr::scene::ISceneManager* p_sceneManager,
					   irr::core::vector3df p_position)
{
	//irr::video::ITexture* texture = p_sceneManager->getVideoDriver()->getTexture("resources/tower-texture.jpg");
	m_animatedMesh = p_sceneManager->getMesh("resources/models/projectile/projectile.3ds");
	
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	//m_meshSceneNode->setMaterialTexture(0, texture);
	m_meshSceneNode->setPosition(p_position);
	
	irr::core::vector3df scale(10.0, 10.0, 10.0);
	
	m_meshSceneNode->setScale(scale);

	SetMaterialFlags();
}

void Projectile::updatePosition()
{
	if (m_from != NULL || m_to != NULL)
	{
		irr::core::vector3df v = getPosition();

		if (m_to->getPosition().X > this->getPosition().X)
			v += irr::core::vector3df(0.05f, 0.0f, 0.0f);
		else if (m_to->getPosition().X < this->getPosition().X)
			v -= irr::core::vector3df(0.05f, 0.0f, 0.0f);

		if (m_to->getPosition().Y > this->getPosition().Y)
			v += irr::core::vector3df(0.0f, 0.05f, 0.0f);
		else if (m_to->getPosition().Y < this->getPosition().Y)
			v -= irr::core::vector3df(0.0f, 0.05f, 0.0f);

		if (m_to->getPosition().Z > this->getPosition().Y)
			v += irr::core::vector3df(0.0f, 0.0f, 0.05f);
		else if (m_to->getPosition().Z < this->getPosition().Z)
			v -= irr::core::vector3df(0.0f, 0.0f, 0.05f);

		setPosition(v);
	}

}

double Projectile::getMovementSpeed()
{
	return m_movementSpeed;
}

double Projectile::getDamage()
{
	return m_damage;
}

Game::Entity* Projectile::getFrom()
{
	return m_from;
}

Game::Entity* Projectile::getTo()
{
	return m_to;
}

void Projectile::setMovementSpeed(double p_movementSpeed)
{
	m_movementSpeed = p_movementSpeed;
}

void Projectile::setDamage(double p_damage)
{
	m_damage = p_damage;
}

void Projectile::setFrom(Game::Entity* p_from)
{
	m_from = p_from;
}

void Projectile::setTo(Game::Entity* p_to)
{
	m_to = p_to;
}
