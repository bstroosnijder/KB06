#ifndef __GAME__KERNEL__H__
#define __GAME__KERNEL__H__

#include "../Camera/Capture.h"
#include "../Camera/Calibration.h"
#include "../Game/EventHandler.h"
#include "../Game/Gui.h"
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
		irr::video::IVideoDriver* m_driver;
		irr::scene::ISceneManager* m_scene;
		Camera::Capture* m_capture;
		Game::Gui* m_gui;
		

		/**
		 * @brief	Show a fps counter in the title of the window
		 */
		void ShowFPS();
	};
}

#endif