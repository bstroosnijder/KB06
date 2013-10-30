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
		 * @brief	Creates a Stargate. TODO!!!!!!!!!!!!!!!!!!!!!!!!!!
		 * @todo inc
		 * @author	Michel van Os.
		 * @param	
		 */
		Stargate(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* p_playgroundListener,
				irr::core::vector3df& p_position);

	   /**
		* @todo
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