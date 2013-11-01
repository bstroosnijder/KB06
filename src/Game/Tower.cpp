#include "Game/Tower.h"

namespace Game
{
	Tower::Tower(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			irr::core::vector3df p_position)
			:
			Entity(p_sceneManager, p_playgroundListener)
	{
		m_shootingSpeed = 1.0f;
		m_shootingRange = 0.0f;
		m_jointCrystal = NULL;

		m_animatedMesh = p_sceneManager->getMesh("resources/models/tower/LOLturret/lolturret1.2.x");

		irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE));
		m_meshSceneNode = animatedMeshSceneNode;
		m_meshSceneNode->setScale(irr::core::vector3df(0.40f, 0.40f, 0.40f));
		if (m_meshSceneNode != NULL)
		{
			// Y = 0.0f So that it stands of the floor correctly
			m_meshSceneNode->setPosition(irr::core::vector3df(p_position.X, 0.0f, p_position.Z));
			m_jointCrystal = animatedMeshSceneNode->getJointNode("shootingbone");
		}

		SetMaterialFlags();

		m_timer = new Timer();

		if (!m_timer->IsRunning())
		{
			m_timer->Start();
		}
	}

	Tower::~Tower()
	{
		delete m_timer;
		m_timer = NULL;
	}

	void Tower::SetShootingSpeed(float p_shootingSpeed)
	{
		m_shootingSpeed = p_shootingSpeed;
	}

	void Tower::SetShootingRange(float p_range)
	{
		m_shootingRange = p_range;
	}

	void Tower::SetShootingDamage(float p_shootingDamage)
	{
		m_shootingDamage = p_shootingDamage;
	}

	float Tower::GetShootingSpeed()
	{
		return m_shootingSpeed;
	}

	float Tower::GetShootingRange()
	{
		return m_shootingRange;
	}

	float Tower::GetShootingDamage()
	{
		return m_shootingDamage;
	}

	void Tower::ShootAtNearestCreature(std::list<Creature*>& p_creatureList)
	{
		if (m_timer->IsRunning() && (m_timer->GetTime() > m_shootingSpeed))
		{
			Creature* creature = SearchNearestCreature(p_creatureList);

			if (creature != NULL)
			{
				ShootProjectileAtCreature(creature);
			}

			m_timer->Reset();
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

			irr::core::vector3df position = m_jointCrystal->getPosition() * m_meshSceneNode->getScale();
			irr::core::vector3df positionCrystal = irr::core::vector3df(position.X, -position.Y, position.Z);
			projectile->SetPosition(GetPosition() - positionCrystal);

			m_playgroundListener->OnProjectileCreated(projectile);
		}
	}
}