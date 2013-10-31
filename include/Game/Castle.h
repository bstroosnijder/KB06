#ifndef __GAME__CASTLE__H__
#define __GAME__CASTLE__H__

#include "Entity.h"

#include <string>

namespace Game
{
	/**
	 * @brief	The Castle is the exit for the Creatures.
	 *			
	 *			Eacht time a Creature reaches the Castle the
	 *			attacker gets points added to his score.
	 *
	 * @author Michel van Os
	 */
	class Castle : public Entity
	{
	public:
		/**
		 * @brief Constructor to initialize a castle
		 *
		 * @param p_sceneManager is used to add the castle scene to the scenemanager.
		 * @param p_playgroundListener is not used at all. But needed because for entity
		 * @param p_position sets the position of the castle
		 */
		Castle(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* p_playgroundListener,
				irr::core::vector3df& p_position);

		/**
		 * @brief	Returns the SceneNode for the joint
		 *			at the begin of the castle path.
		 *
		 * @return  Returns the SceneNode for the joint
		 *			at the begin of the castle path.
		 *
		 * @author	Michel van Os.
		 */
		irr::scene::ISceneNode* GetJointPath();

		/**
		 * @brief	Returns the position of the path joint.
		 * @return	Returns the position of the path joint.
		 * @author	Michel van Os.
		 */
		irr::core::vector3df GetJointPathPosition();

		/**
		 * @brief	Returns the SceneNode for the joint
		 *			at the end of the castle path
		 * @return	Returns the SceneNode for the joint
		 *			at the end of the castle path.
		 *
		 * @author	Michel van Os.
		 */
		irr::scene::ISceneNode* GetJointCenter();

		/**
		 * @brief	Returns the position of the center join.
		 * @return	Returns the position of the center join.
		 *
		 * @author	Michel van Os.
		 */
		irr::core::vector3df GetJointCenterPosition();

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