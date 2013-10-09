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
		irr::scene::ITerrainSceneNode* terrain = p_sceneManager->addTerrainSceneNode(
			"resources/textures/terrain-heightmap.bmp",
			0,                  // parent node
			-1,                 // node id
			irr::core::vector3df(0.f, 0.f, 0.f),     // position
			irr::core::vector3df(0.f, 0.f, 0.f),     // rotation
			irr::core::vector3df(2.f, 0.22f, 2.f)*p_scale,  // scale
			irr::video::SColor ( 255, 255, 255, 255 ),   // vertexColor
			5,                  // maxLOD
			irr::scene::ETPS_17,             // patchSize
			4                   // smoothFactor
			);

		terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		terrain->setMaterialTexture(0, driver->getTexture("resources/textures/terrain-texture.jpg"));
		terrain->setMaterialTexture(1, driver->getTexture("resources/textures/detailmap3.jpg"));
		terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
		terrain->scaleTexture(1.0f, 20.0f);


		// create triangle selector for the terrain	 
		selector = p_sceneManager->createTerrainTriangleSelector(terrain, 0);
		terrain->setTriangleSelector(selector);

		// create collision response animator and attach it to the camera
		irr::scene::ISceneNodeAnimator* anim = p_sceneManager->createCollisionResponseAnimator(
			selector, p_sceneManager->getActiveCamera(), irr::core::vector3df(60,100,60),
			irr::core::vector3df(0,0,0),
			irr::core::vector3df(0,50,0));
		irr::scene::ICameraSceneNode* camera = p_sceneManager->getActiveCamera();
		camera->addAnimator(anim);
		anim->drop();

		return selector;
	}
}