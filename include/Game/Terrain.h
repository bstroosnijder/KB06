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
	 * @todo comments
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

			/**
			* @brief Returns the height of the terrain at the given location.
			* @param p_position is required to find the height of the terrain at the X and Z values of p_position.
			*/
			irr::f32 GetTerrainHeight(irr::core::vector3df p_position);

		   /**
			* @brief Returns the terrain dimensions.
			*/
			irr::core::dimension2d<irr::f32> GetTerrainDimensions();

		   /**
			* @brief ScaleTerrain scales the terrain with the given parameter.
			* @param p_Scaling is the scaling factor to scale the terrain with.
			*/
			void ScaleTerrain(irr::core::vector3df p_Scaling);

		   /**
			* @brief SetPosition adds to the X-position of the terrain.
			* @param p_adjustment is a float to add to the starting x position of the terrain.
			*/
			void SetPosition(float p_adjustment);

	private:
		irr::scene::ITerrainSceneNode* m_terrain;
		irr::core::dimension2d<irr::f32> m_terrainDimensions;
		irr::core::vector3df m_startScaling;
		irr::core::vector3df m_startPosition;

	};
}

#endif