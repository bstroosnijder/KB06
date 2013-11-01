#ifndef __GAME__TERRAIN__H__
#define __GAME__TERRAIN__H__

#include "Defines.h"
#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	This class generates the terrain and manipulates the terrain by scaling and moving it around.
	 *			It also provides the ability to get information about the terrain.
	 *
	 * @author	Albert Haaksema.
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
			* @brief	This function generates the terrain and returns the selectors for collision detection.
			*
			* @param	p_sceneManager is required to add the terrain to the scene and to get the videodrivers.
			* @param	p_scale is used to scale the terrain default is 1.
			* @return	Returns a triangleselector which can be used for collisiondetection purposes with the terrain.
			*/
			irr::scene::ITriangleSelector* GenerateTerrain(irr::scene::ISceneManager* p_sceneManager, float p_scale);

		   /**
			* @brief	Returns the terrain dimensions.
			* @return	Returns a 2 dimensional float with the dimensions of the terrain.
			*/
			irr::core::dimension2d<irr::f32> GetTerrainDimensions();

		   /**
			* @brief	ScaleTerrain scales the terrain with the given parameter.
			* @param	p_Scaling is the scaling factor to scale the terrain with.
			*/
			void ScaleTerrain(irr::core::vector3df p_scaling);

		   /**
			* @brief	SetPosition adds to the X-position of the terrain.
			* @param	p_adjustment is a float to add to the starting x position of the terrain.
			*/
			void SetPosition(float p_adjustment);

	private:
		irr::core::dimension2d<irr::f32> m_terrainDimensions;
		irr::core::vector3df m_startScaling;
		irr::core::vector3df m_startPosition;
		irr::scene::IAnimatedMeshSceneNode* m_terrain;
	};
}

#endif