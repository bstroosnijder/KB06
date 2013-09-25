#include "Game/Tower.h"

using namespace Game;

irr::video::ITexture* texture;


Tower::Tower(irr::scene::ISceneManager* p_sceneManager,
			 irr::core::vector3df p_position)
{
	p_sceneManager->getVideoDriver()->setTextureCreationFlag(irr::video::E_TEXTURE_CREATION_FLAG::ETCF_NO_ALPHA_CHANNEL, false);
	p_sceneManager->getVideoDriver()->setTextureCreationFlag(irr::video::E_TEXTURE_CREATION_FLAG::ETCF_CREATE_MIP_MAPS, false);
	p_sceneManager->getVideoDriver()->setTextureCreationFlag(irr::video::E_TEXTURE_CREATION_FLAG::ETCF_ALWAYS_32_BIT, true);
	p_sceneManager->getVideoDriver()->setTextureCreationFlag(irr::video::E_TEXTURE_CREATION_FLAG::ETCF_ALWAYS_16_BIT, false);

	irr::video::ITexture* texture = p_sceneManager->getVideoDriver()->getTexture("resources/models/syddney.bmp");
	m_animatedMesh = p_sceneManager->getMesh("resources/models/animtest2.x");
	
	m_meshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(m_animatedMesh);
	//m_meshSceneNode->setMaterialTexture(0, texture);

	irr::video::SMaterial mat =	m_meshSceneNode->getMaterial(0);
	irr::video::SMaterial mat2 = m_meshSceneNode->getMaterial(1);

	mat.MaterialType = irr::video::E_MATERIAL_TYPE::EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
	mat2.MaterialType = irr::video::E_MATERIAL_TYPE::EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
	m_meshSceneNode->setMaterialType(irr::video::E_MATERIAL_TYPE::EMT_TRANSPARENT_ADD_COLOR);

	
	m_meshSceneNode->setPosition(p_position);


	irr::video::IVideoDriver* videoDriver = p_sceneManager->getVideoDriver();

	irr::core::vector3df start(0.0f);
	
	texture = m_meshSceneNode->getMaterial(0).getTexture(0);

	//irr::core::vector3df imagePosition(0.0f, 0.0f, 0.0f);
	//irr::core::recti rect(2048, 2048);

	//videoDriver->draw2DImage(texture, 
	
	SetMaterialFlags();
}