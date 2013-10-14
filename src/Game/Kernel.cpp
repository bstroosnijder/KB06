#include "Game/Kernel.h"
#include "Game/Tower.h"

namespace Game
{
	Kernel::Kernel()
	{
		m_title = "KB06: Game";
		m_multiThreaded = false;
		m_device = irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(640, 480));
		m_videoDriver = m_device->getVideoDriver();
		m_guiEnvironment = m_device->getGUIEnvironment();
		m_sceneManager = m_device->getSceneManager();
		m_inputHandler = new InputHandler();
		m_device->setEventReceiver(m_inputHandler);

		// The L is needed to have a long string. Irrlicht uses this. 
		m_device->setWindowCaption(m_title.c_str());
		m_device->setResizable(true);
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
		// Create a webcam capturer
		m_capture = new Camera::Capture(m_multiThreaded, m_videoDriver->addTexture(irr::core::dimension2d<irr::u32>(640, 480), "capture_background"));
		m_capture->SetFov(60.0f);
		m_capture->SetLongestGameLine(irr::core::line2df(
			irr::core::vector2df(0, 0),
			irr::core::vector2df(0, 100)));
		m_inputHandler->AddListener(m_capture);

		// Create a root node for all other nodes to inherit the AR movement
		irr::scene::ISceneNode* root = m_sceneManager->addEmptySceneNode();

		// Create a static camera
		irr::scene::ICameraSceneNode* camera = m_sceneManager->addCameraSceneNode(NULL,
			irr::core::vector3df(0.0f, m_capture->GetPixelDistance(), 1.0f),
			irr::core::vector3df(0.0f, 0.0f, 0.0f));

		// Create a test cube
		irr::scene::ISceneNode* cube = m_sceneManager->addCubeSceneNode(20.0f, root, NULL,
			irr::core::vector3df(0.0f, 10.0f, 0.0f));
		cube->setMaterialTexture(0, m_videoDriver->getTexture("resources\\textures\\purple.jpg"));
		cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		// Game loop
		while (m_device->run())
		{
			// Start the capture thread
			m_capture->Start();
			// Update the camera height
			camera->setPosition(
				irr::core::vector3df(0.0f, m_capture->GetPixelDistance(), 1.0f));
			// Update the games shortest side
			m_capture->GetCalculatedShortestGameLine();

			// Show the fps in the title of the window
			ShowFPS();
			// Begin an empty blue scene
			m_videoDriver->beginScene(true, true, irr::video::SColor(255, 0, 0, 255));

			// Update the texture with the camera capture
			m_videoDriver->draw2DImage(m_videoDriver->getTexture("capture_background"), irr::core::vector2d<irr::s32>(0, 0));
			if (m_capture->HasChosen() && m_capture->IsLost() == false)
			{
				if (m_inputHandler->Contains(m_capture))
				{
					m_inputHandler->RemoveListener(m_capture);
				}

				// Get the transformation matrix needed to transform the world based on the AR
				irr::core::matrix4 transformation = m_capture->GetTransformMatrix(camera->getProjectionMatrix());
				root->setPosition(transformation.getTranslation());
				root->setRotation(transformation.getRotationDegrees());

				/*
					Example code to get start and end points from the capture class.
					*/
				irr::core::vector3df* p_startPoints = new irr::core::vector3df();
				irr::core::vector3df* p_endPoints = new irr::core::vector3df();
				m_capture->FindStartAndEndPoints(m_capture->GetImage(), p_startPoints, p_endPoints);
				
			}

			m_sceneManager->drawAll();
			m_guiEnvironment->drawAll();
			m_videoDriver->endScene();
		}
	}

	void Kernel::SetMultiThreaded(bool p_multiThreaded)
	{
		m_multiThreaded = p_multiThreaded;
	}

	void Kernel::ShowFPS()
	{
		irr::core::stringw title = m_title;
		title += " - FPS: ";
		title += m_videoDriver->getFPS();

		m_device->setWindowCaption(title.c_str());
	}
}