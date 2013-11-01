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
		m_meshSceneNode->setScale(irr::core::vector3df(0.2f, 0.2f, 0.2f));
		m_movementSpeed = 1.2f;
		m_damage = 10;
		irr::core::aabbox3d<irr::f32>* boundingbox = new irr::core::aabbox3d<irr::f32>(irr::core::vector3df(-2.0f, -2.0f, -2.0f), irr::core::vector3df(2.0f, 2.0f, 2.0f));
		m_animatedMesh->setBoundingBox(*boundingbox);
		SetMaterialFlags();


		irr::scene::ITriangleSelector* selector = m_sceneManager->getRootSceneNode()->getTriangleSelector();

		irr::scene::ISceneNodeAnimator* animator = m_sceneManager->createCollisionResponseAnimator(
				selector,
				this->GetSceneNode(),
				irr::core::vector3df(30,  30, 30),
				irr::core::vector3df( 0,  -3,  0),
				irr::core::vector3df( 0,  50,  0));
			

	}

	void Projectile::MoveTowardsTarget(float p_deltaTime)
	{
		if (m_target->GetHealthPoints() > 0.0)
		{
			irr::core::vector3df position = GetPosition();
			irr::core::vector3df target = m_target->GetPosition();

			irr::core::vector3df distance = target - position;
		
			float unitLength = 10.0f;
			float speedScale = unitLength / position.getDistanceFrom(target);

			position = position + distance * m_movementSpeed * speedScale * p_deltaTime * 60;

			SetPosition(position);

			irr::core::aabbox3df boundingboxProjectileNode = m_meshSceneNode->getTransformedBoundingBox();
			irr::core::aabbox3df boundingboxCreatureNode = m_target->GetSceneNode()->getTransformedBoundingBox();

			if (boundingboxProjectileNode.intersectsWithBox(boundingboxCreatureNode))
			{
				m_playgroundListener->OnCreatureHit(m_target, this);
				m_playgroundListener->OnProjectileDestroyed(this);
			}
		}
	}

	float Projectile::GetMovementSpeed()
	{
		return m_movementSpeed;
	}

	float Projectile::GetDamage()
	{
		return m_damage;
	}

	Game::Creature* Projectile::GetTarget()
	{
		return m_target;
	}

	void Projectile::SetMovementSpeed(float p_movementSpeed)
	{
		m_movementSpeed = p_movementSpeed;
	}

	void Projectile::SetDamage(float p_damage)
	{
		m_damage = p_damage;
	}

	void Projectile::SetTarget(Game::Creature* p_target)
	{
		m_target = p_target;
	}
}