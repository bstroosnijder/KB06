#ifndef __GAME__TERRAIN__H__
#define __GAME__TERRAIN__H__

#include "Defines.h"
#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief This class generates the terrain
	 *
	 * @author Albert Haaksema
	 */
	class Terrain
	{
		public:
			/**
			 *@brief Constructor
			 */
			Terrain();

			/**
			 *@brief Destructor
			 */
			~Terrain();

			/**
			 *@brief This function generates the terrain and returns the selectors for collision detection
			 *@param p_sceneManager is required to add the terrain to the scene and to get the videodrivers
			 *@param p_scale is used to scale the terrain default is 1
			 */
			irr::scene::ITriangleSelector* GenerateTerrain(irr::scene::ISceneManager* p_sceneManager, float p_scale);

	};
}

#endif