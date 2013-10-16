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
		 * @brief	Creates a Stargate.
		 *
		 * @author	Michel van Os.
		 * @param	
		 */
		Stargate(irr::scene::ISceneManager* p_sceneManager,
				PlaygroundListener* p_playgroundListener,
				irr::core::vector3df& p_position);
	};
}

#endif