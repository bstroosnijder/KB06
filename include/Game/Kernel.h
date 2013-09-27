#ifndef __GAME__KERNEL__H__
#define __GAME__KERNEL__H__

#include "InputHandler.h"
#include "../Camera/Capture.h"
#include "../Camera/Calibration.h"
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

		/**
		 * @brief	Sets multi threaded
		 * @param	p_multiThreaded Whether to use multithreading or not
		 */
		void SetMultiThreaded(bool p_multiThreaded);

	private:
		irr::core::stringw m_title;
		bool m_multiThreaded;
		irr::IrrlichtDevice* m_device;
		irr::video::IVideoDriver* m_videoDriver;
		irr::gui::IGUIEnvironment* m_guiEnvironment;
		irr::scene::ISceneManager* m_sceneManager;
		InputHandler* m_inputHandler;
		Camera::Capture* m_capture;

		/**
		 * @brief	Show a fps counter in the title of the window
		 */
		void ShowFPS();
	};
}

#endif