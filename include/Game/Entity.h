#ifndef __GAME__OBJECT__H__
#define __GAME__OBJECT__H__

#include "PlaygroundListener.h"

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
		Entity(irr::scene::ISceneManager*, PlaygroundListener*);
		~Entity();

		virtual void Update(float) = 0;
		virtual void updatePosition();
		void Render(irr::scene::ISceneManager* p_sceneManager);
		
		void SetMaterialFlags(irr::scene::ISceneNode* p_sceneNode = NULL);

		irr::core::vector3df GetPosition();
		void SetPosition(irr::core::vector3df& p_position);
		irr::scene::ISceneNode* GetSceneNode();

	protected:
		irr::scene::ISceneManager* m_sceneManager;
		PlaygroundListener* m_playgroundListener;

		irr::scene::ISceneNode* m_meshSceneNode;
		irr::scene::IAnimatedMesh* m_animatedMesh;
	};
}

#endif