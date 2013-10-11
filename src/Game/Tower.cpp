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

Creature* Tower::SearchNearestCreature(std::list<Creature*>* p_creatureList)
{
	float distanceNearest = 0;
	Creature* objectNearest = NULL;

	for (std::list<Creature*>::const_iterator iterator = p_creatureList->begin(), end = p_creatureList->end(); iterator != end; ++iterator)
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

Projectile* Tower::ShootAtTarget(irr::scene::ISceneManager* p_sceneManager)
{
	Projectile* projectile = new Projectile(p_sceneManager, GetPosition());

	projectile->SetPosition(this->GetPosition());
	projectile->SetFrom(this);
	projectile->SetTo(m_target);

	return projectile;
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

void Tower::Update(float)
{
	return;
}