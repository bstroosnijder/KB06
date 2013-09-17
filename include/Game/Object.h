#ifndef __GAME__OBJECT__H__
#define __GAME__OBJECT__H__

#include <irrlicht.h>

namespace Game
{
	class Object
	{
	public:
		Object();

		void SetMaterialFlags();
	protected:
		irr::scene::ISceneNode* m_meshSceneNode;
		irr::scene::IAnimatedMesh* m_animatedMesh;
	};
}

#endif