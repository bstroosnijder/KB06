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
		 * @brief	Set the MaterialFlags for the SceneNode.
		 *
		 *			If p_sceneNode is NULL then the materials of 
		 *			m_meshSceneNode will be changed.
		 * @param	p_sceneNode The ISceneNode the materials should be changed for.
		 */
		void SetMaterialFlags(irr::scene::ISceneNode* p_sceneNode = NULL);

		/**
		 * @brief	Returns the position of the Entity in a vector3df.
		 *
		 * @return	The position of the Entity.
		 */
		irr::core::vector3df GetPosition();

		/**
		 * @brief	Set the position of the Entity.
		 *
		 * @param	p_position The new position of the Entity.
		 */
		void SetPosition(irr::core::vector3df& p_position);

		/**
		 * @brief	Return the SceneNode of the Entity.
		 *
		 * @return	The SceneNode of the Entity.
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