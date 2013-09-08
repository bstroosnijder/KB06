#include "Game/Kernel.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(640, 480));
		m_driver = m_device->getVideoDriver();
		m_scene = m_device->getSceneManager();

		Setup();
	}

	Kernel::~Kernel()
	{
		Cleanup();
	}

	void Kernel::Setup()
	{
		m_device->setWindowCaption(L"KB01: Game");
	}

	void Kernel::Cleanup()
	{
		m_device->drop();
	}

	void Kernel::Start()
	{
		while (m_device->run())
		{
			m_driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));
			m_scene->drawAll();
			m_driver->endScene();
		}
	}
}