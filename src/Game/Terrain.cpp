#include "Game/Terrain.h"

namespace Game
{
	Terrain::Terrain()
	{
		
	}

	Terrain::~Terrain()
	{
		
	}

	irr::scene::ITriangleSelector* Terrain::GenerateTerrain(irr::scene::ISceneManager* p_sceneManager, float p_scale)
	{
		irr::scene::ITriangleSelector* selector;
		irr::scene::IAnimatedMesh* terrainMesh = p_sceneManager->addHillPlaneMesh("plane",
			irr::core::dimension2d<irr::f32>(1, 1),			//Unit size
			irr::core::dimension2d<irr::u32>(100, 100),		//Units
			0,												//
			30.0f);											//Hill height
		terrainMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		m_terrain = p_sceneManager->addAnimatedMeshSceneNode(terrainMesh,
						p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE),	// parent node
			-1,												// node id
			irr::core::vector3df(0.f, 0.f, 0.f),			// position
			irr::core::vector3df(0.f, 0.f, 0.f),			// rotation
			irr::core::vector3df(1.f, 0.5f, 1.f)*p_scale);	// scale);

		
		m_terrain->setVisible(true);
		irr::video::IVideoDriver* driver = p_sceneManager->getVideoDriver();
		m_terrain->setMaterialTexture(0, driver->getTexture("resources/textures/terrain-texture.jpg"));
		selector = p_sceneManager->createTriangleSelector(m_terrain);


		m_terrainDimensions.Width = 100 * p_scale;
		m_terrainDimensions.Height = 100 * p_scale;

		irr::core::vector3df adjustment;
		adjustment.X = m_terrain->getPosition().X - (m_terrainDimensions.Width / 2);
		adjustment.Z = m_terrain->getPosition().Z - (m_terrainDimensions.Height / 2);
		adjustment.Y = m_terrain->getPosition().Y;
		m_terrain->setPosition(adjustment);

		m_startScaling = m_terrain->getScale();
		m_startPosition = m_terrain->getPosition();
		return selector;
	}

	irr::core::dimension2d<irr::f32> Terrain::GetTerrainDimensions()
	{
		return m_terrainDimensions;
	}

	void Terrain::ScaleTerrain(irr::core::vector3df p_scaling)
	{
		irr::core::vector3df scaling = m_startScaling;
		scaling *= p_scaling;
		m_terrain->setScale(scaling);

	}

	void Terrain::SetPosition(float p_adjustment)
	{
		irr::core::vector3df adjustment = m_startPosition;
		adjustment.X += p_adjustment;
		m_terrain->setPosition(adjustment);			
	}
}