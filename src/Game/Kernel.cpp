#include "Game/Kernel.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(640, 480));
		m_driver = m_device->getVideoDriver();
		m_scene = m_device->getSceneManager();
		m_capture = new Camera::Capture(m_driver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "capture_background"));

		m_device->setWindowCaption(L"KB01: Game");
		m_scene->addCameraSceneNode(NULL, irr::core::vector3df(100.0f, 100.0f, 150.0f), irr::core::vector3df(0.0f, 0.0f, 0.0f));
		irr::scene::ISceneNode* cube = m_scene->addCubeSceneNode(50.0f, NULL, NULL, irr::core::vector3df(0.0f, 0.0f, 0.0f));
		cube->setMaterialTexture(0, m_driver->getTexture("resources\\textures\\purple.jpg"));
		cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	Kernel::~Kernel()
	{
		Cleanup();
	}

	void Kernel::Cleanup()
	{
		if (m_capture)
		{
			delete m_capture;
		}

		m_device->drop();
	}

	void Kernel::Start()
	{
		while (m_device->run())
		{
			// Update the texture with the camera capture
			m_capture->UpdateTexture();

			m_driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));
			m_driver->draw2DImage(m_driver->getTexture("capture_background"), irr::core::vector2d<irr::s32>(0, 0));
			m_scene->drawAll();
			m_driver->endScene();

			ShowFPS();
		}
	}

	void Kernel::ShowFPS()
	{
		irr::core::stringw title = "KB01: Game";
		title += " - FPS: ";
		title += m_driver->getFPS();

		m_device->setWindowCaption(title.c_str());
	}
}