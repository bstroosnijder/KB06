#ifndef __GAME__OBJECT__H__
#define __GAME__OBJECT__H__

#include <irrlicht.h>

namespace Game
{
	/**
	* @brief	General entity class.
	* @author	Thomas Gravekamp
	*/
	class Entity
	{
	public:
		Entity();

		void SetMaterialFlags();
		virtual void updatePosition();
		void Render(irr::scene::ISceneManager* p_sceneManager);

		irr::core::vector3df getPosition();
		void setPosition(irr::core::vector3df p_vector);

		

	protected:
		irr::scene::ISceneNode* m_meshSceneNode;
		irr::scene::IAnimatedMesh* m_animatedMesh;
	};
}

#endif