#ifndef __GAME__KERNEL__H__
#define __GAME__KERNEL__H__

#include "../Camera/Capture.h"
#include "../Camera/Calibration.h"
#include "InputHandler.h"
#include "GameManager.h"

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
		 * @brief	Sets multithreaded
		 * @param	p_multiThreaded Value
		 */
		void SetMultiThreaded(bool p_multiThreaded);

	private:
		irr::IrrlichtDevice* m_device;
		bool m_multiThreaded;

		InputHandler* m_inputHandler;
		GameManager* m_gameManager;
	};
}

#endif