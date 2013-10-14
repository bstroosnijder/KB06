#include "Game/Projectile.h"

using namespace Game;

Projectile::Projectile(
		irr::scene::ISceneManager* p_sceneManager,
		PlaygroundListener* p_playgroundListener,
		irr::core::vector3df p_position)
		:
		Entity(p_sceneManager, p_playgroundListener)
{
	//irr::video::ITexture* texture = p_sceneManager->getVideoDriver()->getTexture("resources/tower-texture.jpg");
	m_animatedMesh = p_sceneManager->getMesh("resources/models/projectile/projectile.3ds");
	
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	//m_meshSceneNode->setMaterialTexture(0, texture);
	m_meshSceneNode->setPosition(p_position);
	
	//irr::core::vector3df scale(10.0, 10.0, 10.0);
	
	//m_meshSceneNode->setScale(scale);

	SetMaterialFlags();
}

void Projectile::Update(float p_deltaTime)
{
	
}

void Projectile::MoveTowardsTarget(float p_deltaTime)
{
	if (m_target != NULL)
	{
		irr::core::vector3df position = GetPosition();
		irr::core::vector3df target = m_target->GetPosition();

		irr::core::vector3df distance = target - position;
		
		float unitLength = 10.0f;
		float speed = 0.04f;
		float speedScale = unitLength / position.getDistanceFrom(target);

		position = position + speed * speedScale * p_deltaTime * 60;


		int x = 0;
	}

		/*
	if (m_from != NULL && m_to != NULL)
	{
		irr::core::vector3df v = GetPosition();

		if (m_to->GetPosition().X > this->GetPosition().X)
			v += irr::core::vector3df(0.05f, 0.0f, 0.0f);
		else if (m_to->GetPosition().X < this->GetPosition().X)
			v -= irr::core::vector3df(0.05f, 0.0f, 0.0f);

		if (m_to->GetPosition().Y > this->GetPosition().Y)
			v += irr::core::vector3df(0.0f, 0.05f, 0.0f);
		else if (m_to->GetPosition().Y < this->GetPosition().Y)
			v -= irr::core::vector3df(0.0f, 0.05f, 0.0f);

		if (m_to->GetPosition().Z > this->GetPosition().Z)
			v += irr::core::vector3df(0.0f, 0.0f, 0.05f);
		else if (m_to->GetPosition().Z < this->GetPosition().Z)
			v -= irr::core::vector3df(0.0f, 0.0f, 0.05f);

		SetPosition(v);
	}
		*/

}

double Projectile::GetMovementSpeed()
{
	return m_movementSpeed;
}

double Projectile::GetDamage()
{
	return m_damage;
}

Game::Creature* Projectile::GetTarget()
{
	return m_target;
}

void Projectile::SetMovementSpeed(double p_movementSpeed)
{
	m_movementSpeed = p_movementSpeed;
}

void Projectile::SetDamage(double p_damage)
{
	m_damage = p_damage;
}

void Projectile::SetTarget(Game::Creature* p_target)
{
	m_target = p_target;
}
