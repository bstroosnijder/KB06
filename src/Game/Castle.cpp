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
		m_meshSceneNode->setScale(irr::core::vector3df(0.30f,0.30f,0.30f));
		/*	
		int jointCount = animatedMeshSceneNode->getJointCount();

		for (int i = 0; i < jointCount; i++)
		{
			irr::scene::IBoneSceneNode* bone = animatedMeshSceneNode->getJointNode(i);
		}
		*/

		SetMaterialFlags();
	}
}