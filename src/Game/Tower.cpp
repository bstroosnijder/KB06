#include "Game/Tower.h"

using namespace Game;

Tower::Tower(irr::scene::ISceneManager* p_sceneManager)
{
	m_animatedMesh = p_sceneManager->getMesh("resources/models/sydney.md2");
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);

	p_sceneManager->addMeshSceneNode(m_animatedMesh);
}