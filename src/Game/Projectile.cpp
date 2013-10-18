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
		m_animatedMesh = p_sceneManager->getMesh("resources/models/projectile/companion_cubev02.X");
	
		m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
		m_meshSceneNode->setPosition(p_position);

		m_movementSpeed = 0.2f;
		m_damage = 100;
	
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
			float speedScale = unitLength / position.getDistanceFrom(target);

			position = position + distance * m_movementSpeed * speedScale * p_deltaTime * 60;
		//Alex why commented
			SetPosition(position);
		}
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