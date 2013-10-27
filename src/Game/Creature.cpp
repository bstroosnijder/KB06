#include "Game/Creature.h"

namespace Game
{
	Creature::Creature(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			irr::core::vector3df p_position,
			PathRoute* p_pathRoute)
			:
			PathFollower(p_sceneManager, p_playgroundListener, p_pathRoute)
	{
		m_meshSceneNode = p_sceneManager->addEmptySceneNode(p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE));
		irr::scene::ISceneNode* sceneNodeTemp = NULL;

		//Head
		m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk2.7H.x");
		sceneNodeTemp = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
		SetMaterialFlags(sceneNodeTemp);
	
		//Body
		m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk2.7L.x");///testanim1.1.x"); AlexH waarom staat dit hier?
		sceneNodeTemp = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
		SetMaterialFlags(sceneNodeTemp);

		//Left Foot
		m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk2.7LF.x");
		sceneNodeTemp = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
		SetMaterialFlags(sceneNodeTemp);

		//Right Foot
		m_animatedMesh = p_sceneManager->getMesh("resources/models/creature/goomba/goombawalk2.7RF.x");
		sceneNodeTemp = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, m_meshSceneNode);
		SetMaterialFlags(sceneNodeTemp);
		m_meshSceneNode->setScale(irr::core::vector3df(0.50f,0.50f,0.50f));
		m_healthPoints = 100;

		StartFollowing();
	}

	Creature::~Creature()
	{

	}

	void Creature::FollowPath(float p_deltaTime, Terrain* p_terrain)
	{
		//Move along path
		PathFollower::FollowPath(p_deltaTime);

		//Determine new position
		irr::core::vector3df position = GetPosition();
		
		position.Y = p_terrain->GetTerrainHeight(position);
		SetPosition(position);

		if (IsEndOfRouteReached())
		{
			m_playgroundListener->OnCreatureRouteEndReached(this);
		}
	}

	void Creature::SetHealthPoints(int p_healthPoints)
	{
		m_healthPoints = p_healthPoints;
	}

	int Creature::GetHealthPoints()
	{
		return m_healthPoints;
	}
}