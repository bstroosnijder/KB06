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
		m_jointCrystal = NULL;

		m_animatedMesh = p_sceneManager->getMesh("resources/models/tower/LOLturret/lolturret1.2.x");

		irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
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
		Creature* targetCreature = NULL;
		float targetDistance = -1;

		std::list<Creature*>::iterator creatureIt;
		std::list<Creature*>::iterator creatureItEnd = p_creatureList.end();
		Creature* creatureCurrent = NULL;
		float creatureDistance;

		for (creatureIt = p_creatureList.begin(); creatureIt != creatureItEnd; ++creatureIt)
		{
			creatureCurrent = (*creatureIt);
			creatureDistance = GetPosition().getDistanceFrom(creatureCurrent->GetPosition());

			if (targetDistance ==  -1 || creatureDistance < targetDistance)
			{
				targetDistance = creatureDistance;
				targetCreature = creatureCurrent;
			}
		}

		return targetCreature;
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