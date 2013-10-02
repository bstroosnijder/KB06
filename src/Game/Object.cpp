#include "Game/Object.h"

namespace Game
{
	Object::Object()
	{
		m_meshSceneNode = NULL;
		m_animatedMesh = NULL;
	}

	void Object::SetMaterialFlags()
	{
		m_meshSceneNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
		m_meshSceneNode->setMaterialFlag(irr::video::E_MATERIAL_FLAG::EMF_ANTI_ALIASING, true);
	}
}