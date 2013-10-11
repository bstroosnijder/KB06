#ifndef __GAME__KERNEL__H__
#define __GAME__KERNEL__H__

#include "../Camera/Capture.h"
#include "../Camera/Calibration.h"
#include "../Game/EventHandler.h"
#include "../Game/Gui.h"
#include "GameManager.h"
#include "Playground.h"
#include "DeltaTimer.h"

#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	This class will help with the initialization of all the core systems
	 *			that we need for the game to run properly.
	 * @author	Bas Stroosnijder
	 */
	class Kernel
	{
	public:
		/**
		 * @brief	Constructor
		 */
		Kernel();

		/**
		 * @brief	Destructor
		 * @see		Kernel::Cleanup
		 */
		~Kernel();

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();

		/**
		 * @brief	Starts the main game loop
		 */
		void Start();

	private:
		irr::IrrlichtDevice* m_device;
		irr::video::IVideoDriver* m_videoDriver;
		irr::scene::ISceneManager* m_sceneManager;
		Camera::Capture* m_capture;

		Game::Gui* m_gui;
		irr::scene::ICameraSceneNode* m_camera;
		Playground* m_playground;
		//GameManager* m_gameManager;
		DeltaTimer* m_deltaTimer;		

		/**
		 * @brief	Show a fps counter in the title of the window
		 */
		void ShowFPS();
	};
}

#endif