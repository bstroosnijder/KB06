#ifndef __GAME__STARGATE__H__
#define __GAME__STARGATE__H__

#include "Entity.h"

namespace Game
{
	/**
	* @brief	The Stargate is used as the spawn point for Creatures.
	*
	*			The Creatures will be spawned at the Stargate. From that
	*			the creatures will following the path towards the Castle.
	* @author	Michel van Os.
	*/
	class Stargate : public Entity
	{
	public:
		/**
		* @brief	Initializes a new Stargate object with a mesh and position. Also sets the playground listener to trigger events in the playground.
		* @param	p_sceneManager			Reference to the irrlicht scene manager
		* @param	p_playgroundListener	Reference to the playground listener
		* @param	p_position				The position of the stargate
		* @author	Michel van Os.
		*/
		Stargate(irr::scene::ISceneManager* p_sceneManager,
			PlaygroundListener* p_playgroundListener,
			irr::core::vector3df& p_position);
		/**
		* @brief	Gets the joint base. This is the point from where the creatures start walking towards the pencils (if they are present) or towards the castle.
		* @return	Returns a ISceneNode from where the creatures start walking towards the end.
		*/
		irr::scene::ISceneNode* GetJointBase();

		/**
		 * @brief	Moves the Stargate so that the base joint 
		 *			is placed at p_position.
		 *
		 * @author	Michel van Os.
		 * @param	p_position The position for the base joint.
		 */
		void SetPositionToJointBase(irr::core::vector3df p_position);

	private:
		irr::scene::ISceneNode* m_jointBase;
	};
}

#endif