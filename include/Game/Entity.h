#ifndef __GAME__OBJECT__H__
#define __GAME__OBJECT__H__

#include "Defines.h"
#include "PlaygroundListener.h"

#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	General entity class.
	 *
	 * @author	Thomas Gravekamp
	 * @todo		Comment private parts.
	 */
	class Entity
	{
	public:
		/**
		 * @brief	Constructor override with a Scenemanager to attach itself to.
		 *
		 * @param	SceneManager is required to attach the entity scenenode to the manager
		 * @param	The PlaygroundListener is used to sent events to the playground
		 */
		Entity(irr::scene::ISceneManager*, PlaygroundListener*);
		
		/**
		 * @brief	Destructor
		 */
		~Entity();

		/**
		 * @brief	Render the entity
		 * @param	p_sceneManager
		 */
		void Render(irr::scene::ISceneManager* p_sceneManager);
		
		/**
		 * @brief	Set the MaterialFlags of the entity
		 * @param	The MaterialFlags of the p_sceneNode will be changed
		 */
		void SetMaterialFlags(irr::scene::ISceneNode* p_sceneNode = NULL);

		/**
		 * @brief	Return the position of the entity in a vector3df
		 */
		irr::core::vector3df GetPosition();

		/**
		 * @brief	Set the position of the entity
		 * @param	p_position is the new position of the entity
		 */
		void SetPosition(irr::core::vector3df& p_position);

		/**
		 * @brief	Return the SceneNode of the entity
		 */
		irr::scene::ISceneNode* GetSceneNode();

	protected:
		irr::scene::ISceneManager* m_sceneManager;
		PlaygroundListener* m_playgroundListener;

		irr::scene::ISceneNode* m_meshSceneNode;
		irr::scene::IAnimatedMesh* m_animatedMesh;
	};
}

#endif