#include "Game/Terrain.h"

namespace Game
{
	Terrain::Terrain()
	{
		
	}

	irr::scene::ITriangleSelector* Terrain::GenerateTerrain(irr::scene::ISceneManager* p_sceneManager, float p_scale)
	{
		irr::scene::ITriangleSelector* selector;
		irr::scene::IAnimatedMesh* aMesh = p_sceneManager->addHillPlaneMesh("plane",
			irr::core::dimension2d<irr::f32>(1,1),
			irr::core::dimension2d<irr::u32>(100,100));
		aMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		m_animatedMeshSceneNode = p_sceneManager->addAnimatedMeshSceneNode(aMesh,
						p_sceneManager->getSceneNodeFromId(C_EMPTY_ROOT_SCENENODE),	// parent node
			-1,												// node id
			irr::core::vector3df(0.f, 0.f, 0.f),			// position
			irr::core::vector3df(0.f, 0.f, 0.f),			// rotation
			irr::core::vector3df(1.f, 0.5f, 1.f)*p_scale);	// scale);

		m_animatedMeshSceneNode->setVisible(false);

		selector = p_sceneManager->createTriangleSelector(m_animatedMeshSceneNode);

		m_startScaling = m_animatedMeshSceneNode->getScale();
		m_startPosition = m_animatedMeshSceneNode->getPosition();
		m_terrainDimensions.Width = 100;
		m_terrainDimensions.Height = 100;

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
		m_animatedMeshSceneNode->setScale(scaling);

	}

	void Terrain::SetPosition(float p_adjustment)
	{
		irr::core::vector3df adjustment = m_startPosition;
		adjustment.X += p_adjustment;
		m_animatedMeshSceneNode->setPosition(adjustment);			
	}
}