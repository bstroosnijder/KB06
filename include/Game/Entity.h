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

<<<<<<< HEAD
		void SetMaterialFlags();
		virtual void updatePosition();
=======
>>>>>>> aa1056c071da2b56e6ed3046a022ae59c3ecf056
		void Render(irr::scene::ISceneManager* p_sceneManager);
		
		void SetMaterialFlags();
		irr::core::vector3df GetPosition();
		void SetPosition(irr::core::vector3df& p_position);

		irr::core::vector3df getPosition();
		void setPosition(irr::core::vector3df p_vector);

		

	protected:
		irr::scene::ISceneNode* m_meshSceneNode;
		irr::scene::IAnimatedMesh* m_animatedMesh;
	};
}

#endif