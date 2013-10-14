#include "Game/Tower.h"

using namespace Game;

Tower::Tower(irr::scene::ISceneManager* p_sceneManager,
			 irr::core::vector3df p_position)
{
	m_shootingSpeed = 0.0f;
	m_range = 0.0f;
	m_target = NULL;
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

double Tower::GetShootingSpeed()
{
	return m_shootingSpeed;
}

double Tower::GetRange()
{
	return m_range;
}

void Tower::SetShootingSpeed(double p_shootingSpeed)
{
	m_shootingSpeed = p_shootingSpeed;
}

void Tower::SetRange(double p_range)
{
	m_range = p_range;
}

void Tower::Update(float p_deltaTime)
{
	return;
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
		projectile->SetFrom(this);
		projectile->SetTo(p_creature);

		m_playgroundListener->ProjectileCreated(projectile);
	}
}