#include "Game/Tower.h"

using namespace Game;

Tower::Tower(irr::scene::ISceneManager* p_sceneManager,
			 irr::core::vector3df p_position)
{
	irr::video::ITexture* texture = p_sceneManager->getVideoDriver()->getTexture("resources/models/sydney.bmp");
	m_animatedMesh = p_sceneManager->getMesh("resources/models/sydney.md2");
	
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	m_meshSceneNode->setMaterialTexture(0, texture);
	m_meshSceneNode->setPosition(p_position);
	
	SetMaterialFlags();
}