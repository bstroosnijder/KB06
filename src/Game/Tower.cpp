#include "Game/Tower.h"

namespace Game
{
	Tower::Tower(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			irr::core::vector3df p_position)
			:
			Entity(p_sceneManager, p_playgroundListener)
	{
		m_shootingSpeed = 0.0f;
		m_shootingRange = 0.0f;
		m_target = NULL;
		m_jointCrystal = NULL;

		m_animatedMesh = p_sceneManager->getMesh("resources/models/tower/LOLturret/lolturret1.2.x");

		irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE));
		m_meshSceneNode = animatedMeshSceneNode;

		if (m_meshSceneNode != NULL)
		{
			m_meshSceneNode->setPosition(p_position);
			m_jointCrystal = animatedMeshSceneNode->getJointNode("shootingbone");
		}


		SetMaterialFlags();
	}

	void Tower::SetShootingSpeed(double p_shootingSpeed)
	{
		m_shootingSpeed = p_shootingSpeed;
	}

	void Tower::SetRange(double p_range)
	{
		m_shootingRange = p_range;
	}

	double Tower::GetShootingSpeed()
	{
		return m_shootingSpeed;
	}

	double Tower::GetRange()
	{
		return m_shootingRange;
	}

	void Tower::ShootAtNearestCreature(std::list<Creature*>& p_creatureList)
	{
		Creature* creature = SearchNearestCreature(p_creatureList);

		if (creature != NULL)
		{
			ShootProjectileAtCreature(creature);
		}
	}

	Creature* Tower::SearchNearestCreature(std::list<Creature*>& p_creatureList)
	{
		float distanceNearest = 0;
		Creature* objectNearest = NULL;

		for (std::list<Creature*>::const_iterator iterator = p_creatureList.begin(), end = p_creatureList.end(); iterator != end; ++iterator)
		{
			float x = GetPosition().X - (*iterator)->GetPosition().X;
			float y = GetPosition().Y - (*iterator)->GetPosition().Y;

			float result = std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f));

			if (distanceNearest == 0)
			{
				distanceNearest = result;
			}
			else if (result < distanceNearest)
			{
				distanceNearest = result;
				objectNearest = (*iterator);
			}
		}
	
		m_target = objectNearest;
	
		return objectNearest;
	}

	void Tower::ShootProjectileAtCreature(Creature* p_creature)
	{
		if (p_creature != NULL)
		{
			Projectile* projectile = new Projectile(m_sceneManager, m_playgroundListener, GetPosition());
			projectile->SetTarget(p_creature);

			m_playgroundListener->ProjectileCreated(projectile);
		}
	}
}