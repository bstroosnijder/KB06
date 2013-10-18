#include "Game/Projectile.h"

namespace Game
{
	Projectile::Projectile(
			irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			irr::core::vector3df p_position)
			:
			Entity(p_sceneManager, p_playgroundListener)
	{
		m_animatedMesh = p_sceneManager->getMesh("resources/models/projectile/creature.3ds");
	
		m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
		m_meshSceneNode->setPosition(p_position);
	
		SetMaterialFlags();
	}

	///@todo	Check if the movement is correct
	void Projectile::MoveTowardsTarget(float p_deltaTime)
	{
		if (m_target != NULL)
		{
			irr::core::vector3df position = GetPosition();
			irr::core::vector3df target = m_target->GetPosition();

			irr::core::vector3df distance = target - position;
		
			float unitLength = 10.0f;
			float speed = 5.0f;
			float speedScale = unitLength / position.getDistanceFrom(target);

			position = position + (speed * speedScale * p_deltaTime * 60);

			SetPosition(position);
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
}