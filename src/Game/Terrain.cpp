#include "Game/Terrain.h"

namespace Game
{
	Terrain::Terrain()
	{
	}

	irr::scene::ITriangleSelector* Terrain::GenerateTerrain(irr::scene::ISceneManager* p_sceneManager, float p_scale)
	{
		irr::scene::ITriangleSelector* selector;
		irr::video::IVideoDriver* driver = p_sceneManager->getVideoDriver();
		m_terrain = p_sceneManager->addTerrainSceneNode(
				"resources/textures/terrain-heightmap.bmp",
				p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE),	// parent node
				-1,												            // node id
				irr::core::vector3df(-300.f, -300.f, -300.f),	            // position
				irr::core::vector3df(0.f, 0.f, 0.f),			            // rotation
				irr::core::vector3df(2.f, 0.22f, 2.f)*p_scale,	            // scale
				irr::video::SColor ( 255, 255, 255, 255 ),		            // vertexColor
				5,												            // maxLOD
				irr::scene::ETPS_17,							            // patchSize
				4												            // smoothFactor
				);

		m_terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		m_terrain->setMaterialTexture(0, driver->getTexture("resources/textures/terrain-texture.jpg"));
		m_terrain->setMaterialTexture(1, driver->getTexture("resources/textures/detailmap3.jpg"));
		m_terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
		m_terrain->scaleTexture(1.0f, 20.0f);

		// create triangle selector for the terrain	 
		selector = p_sceneManager->createTerrainTriangleSelector(m_terrain, 0);
		m_terrain->setTriangleSelector(selector);

		return selector;
	}

	irr::f32 Terrain::GetTerrainHeight(irr::core::vector3df p_position)
	{
		return m_terrain->getHeight(p_position.X, p_position.Z);
	}
}