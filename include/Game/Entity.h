#ifndef __GAME__OBJECT__H__
#define __GAME__OBJECT__H__

#include <irrlicht.h>

namespace Game
{
	class Entity
	{
	public:
		Entity();

		void SetMaterialFlags();
		void Render(irr::scene::ISceneManager* p_sceneManager);

	protected:
		irr::scene::ISceneNode* m_meshSceneNode;
		irr::scene::IAnimatedMesh* m_animatedMesh;
	};
}

#endif