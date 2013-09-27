#include "Game/Entity.h"

using namespace Game;

Entity::Entity()
{
	m_meshSceneNode = NULL;
	m_animatedMesh = NULL;
}

void Entity::SetMaterialFlags()
{
	m_meshSceneNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
	m_meshSceneNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_ANTI_ALIASING, true);
	m_meshSceneNode->setMaterialType(irr::video::E_MATERIAL_TYPE::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
}