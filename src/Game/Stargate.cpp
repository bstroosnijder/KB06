#include "Game/Stargate.h"

namespace Game
{
	Stargate::Stargate(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			irr::core::vector3df& p_position)
			:
			Entity(p_sceneManager, p_playgroundListener)
	{
		m_animatedMesh = p_sceneManager->getMesh("resources/models/stargate/Stargatev01.x");
		
		irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE));
		m_meshSceneNode = animatedMeshSceneNode;
		m_meshSceneNode->setPosition(p_position);

		m_jointBase = NULL;
		
		int jointCount = animatedMeshSceneNode->getJointCount();

		for (int i = 0; i < jointCount; i++)
		{
			irr::scene::IBoneSceneNode* bone = animatedMeshSceneNode->getJointNode(i);
			irr::core::stringw name = bone->getName();

			if (name == "polySurface18")
			{
				m_jointBase = bone;
			}
		}

		SetMaterialFlags();
	}

	irr::scene::ISceneNode* Stargate::GetJointBase()
	{
		return m_jointBase;
	}

	void Stargate::SetPositionToJointBase(irr::core::vector3df p_position)
	{
		SetPosition(p_position +  m_jointBase->getPosition());
	}
}