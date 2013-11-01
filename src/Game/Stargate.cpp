#include "Game/Stargate.h"

namespace Game
{
	Stargate::Stargate(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			irr::core::vector3df& p_position)
			:
			Entity(p_sceneManager, p_playgroundListener)
	{
		m_animatedMesh = p_sceneManager->getMesh("resources/models/stargate/stargatev04/stargatev04.X");//Stargatev01.x");
		
		irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE));
		m_meshSceneNode = animatedMeshSceneNode;
		m_meshSceneNode->setPosition(p_position);
		m_meshSceneNode->setScale(irr::core::vector3df(5.0f));

		m_jointBase = NULL;
		
		int jointCount = animatedMeshSceneNode->getJointCount();

		for (int i = 0; i < jointCount; i++)
		{
			irr::scene::IBoneSceneNode* bone = animatedMeshSceneNode->getJointNode(i);
			irr::core::stringw name = bone->getName();

			if (name == "spawnpointbone")
			{
				m_jointBase = bone;
			}
			else if (name == "endpointbone")
			{
				m_jointPath = bone;
			}
		}
		
		SetPositionToJointBase(p_position);
		SetMaterialFlags();
	}

	irr::scene::ISceneNode* Stargate::GetJointBase()
	{
		return m_jointBase;
	}

	irr::scene::ISceneNode* Stargate::GetJointPath()
	{
		return m_jointBase;
	}

	irr::core::vector3df Stargate::GetJointBasePosition()
	{
		return GetPosition() + m_jointBase->getPosition();
	}

	irr::core::vector3df Stargate::GetJointPathPosition()
	{
		return GetPosition() + m_jointPath->getPosition();
	}

	void Stargate::SetPositionToJointBase(irr::core::vector3df p_position)
	{
		SetPosition(p_position +  m_jointBase->getPosition());
	}
}