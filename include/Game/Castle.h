#ifndef __GAME__CASTLE__H__
#define __GAME__CASTLE__H__

#include "Entity.h"

#include <string>

namespace Game
{
	/**
	 * @brief Contains a Castle.
	 * @author Michel van Os
	 */
	class Castle : public Entity
	{
	public:
		/**
		 * @brief Constructor to initialize a castle
		 * @param p_sceneManager is used to add the castle scene to the scenemanager.
		 * @param p_position sets the position of the castle
		 */
		Castle(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* p_playgroundListener,
				irr::core::vector3df& p_position);

		/**
		 * @brief	Returns the SceneNode for the joint
		 *			at the begin of the castle path.
		 *
		 * @author	Michel van Os.
		 */
		irr::scene::ISceneNode* GetJointPath();

		/**
		 * @biref	Returns the SceneNode for the joint
		 *			at the end of the castle path.
		 *
		 * @author	Michel van Os.
		 */
		irr::scene::ISceneNode* GetJointCenter();

		/**
		 * @brief	Moves the Castle so that the center joint 
		 *			is placed at p_position.
		 *
		 * @author	Michel van Os.
		 * @param	p_position The position for the center joint.
		 */
		void SetPositionToJointCenter(irr::core::vector3df p_position);

	private:
		irr::scene::IBoneSceneNode* m_jointPath;
		irr::scene::IBoneSceneNode* m_jointCenter;
	};
}

#endif