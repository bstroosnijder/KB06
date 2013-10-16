#include "Game/Kernel.h"
#include "Game/Tower.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1280, 720));

		if (!m_device)
		{
			Utility::Logger* logger = Utility::Logger::GetInstance();
			logger->Log(Utility::Logger::LogMessageType::LOG_ERROR, "Failed to create IDevice");
			return;
		}

		m_capture = NULL;
		m_gameManager = new GameManager(m_device);
	}

	Kernel::~Kernel()
	{
		Cleanup();
	}

	void Kernel::Cleanup()
	{
		if (m_gameManager != NULL)
		{
			delete m_gameManager;
			m_gameManager = NULL;
		}

		if (m_capture != NULL)
		{
			delete m_capture;
		}

		m_device->drop();
		delete m_deltaTimer;
	}

	void Kernel::Start()
	{
		while (m_device->run())
		{
			m_gameManager->GameTick();
		}
	}
}