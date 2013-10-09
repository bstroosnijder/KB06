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

		virtual void updatePosition();
		void Render(irr::scene::ISceneManager* p_sceneManager);
		
		void SetMaterialFlags();

		irr::core::vector3df GetPosition();
		void SetPosition(irr::core::vector3df& p_position);

		

	protected:
		irr::scene::ISceneNode* m_meshSceneNode;
		irr::scene::IAnimatedMesh* m_animatedMesh;
	};
}

#endif