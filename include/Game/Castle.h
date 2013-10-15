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
		Castle(irr::scene::ISceneManager* p_sceneManager, irr::core::vector3df& p_position);
	};
}

#endif