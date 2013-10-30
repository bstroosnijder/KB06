#include "Game/Castle.h"

namespace Game
{
	Castle::Castle(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			irr::core::vector3df& p_position)
			:
			Entity(p_sceneManager, p_playgroundListener)
	{
		m_animatedMesh = p_sceneManager->getMesh("resources/models/castle/castleofpeaches1.2.x");
	
		irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh, p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE));
		m_meshSceneNode = animatedMeshSceneNode;
		m_meshSceneNode->setPosition(p_position);
		m_meshSceneNode->setScale(irr::core::vector3df(25.f, 25.f, 25.f));

		m_jointPath = NULL;
		m_jointCenter = NULL;
		
		int jointCount = animatedMeshSceneNode->getJointCount();

		irr::core::vector3df pos2 = GetPosition();

		for (int i = 0; i < jointCount; i++)
		{
			irr::scene::IBoneSceneNode* bone = animatedMeshSceneNode->getJointNode(i);
			std::string name = bone->getName();

			irr::core::vector3df pos = bone->getPosition();

			if (name.compare("padjoint"))
			{
				m_jointPath = bone;
			}
			else if (name.compare("centerjoint"))
			{
				m_jointCenter = bone;
			}
		}
		
		SetMaterialFlags();
	}

	irr::scene::ISceneNode* Castle::GetJointPath()
	{
		return m_jointPath;
	}

	irr::scene::ISceneNode* Castle::GetJointCenter()
	{
		return m_jointCenter;
	}

	void Castle::SetPositionToJointCenter(irr::core::vector3df p_position)
	{
		SetPosition(p_position +  m_jointCenter->getPosition());
	}
}