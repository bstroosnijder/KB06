#ifndef __EventHandler__H__
#define __EventHandler__H__

#include <irrlicht.h>
#include "Game/Gui.h"
#include "Game/Playground.h"

namespace Game
{
	/**
	 * @brief	This Class creates handles incoming events from different inputs.
	 *			
	 * @author	Bram van Elderen
	 */
	class EventHandler	:	public irr::IEventReceiver
	{
		enum
		{
			QUIT_BUTTON = 101,
			MENU_BUTTON = 102,
			ClEAR_BUTTON = 103,
			TOWER_BUTTON = 104,
			SELL_BUTTON = 105,
			CONTROLS_BUTTON = 107,
			STARTGAME_BUTTON = 108
		};

		enum ClickEvent
		{
			TOWER_PRESSED = 1,
			SELL_PRESSED = 2
		};

	public:
		
		/**
		 * @brief Constructor TODO
		 */
		EventHandler(irr::IrrlichtDevice* p_device, Game::Gui* p_gui, Game::Playground* p_playground);
		
		/**
		 * @brief Deconstructor TODO
		 */
		~EventHandler();

		/**
		 * @brief handles events TODO
		 */
		virtual bool OnEvent(const irr::SEvent& event);

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();

	private:
		Game::Gui* m_gui;
		Game::Playground* m_playground;
		irr::IrrlichtDevice* m_device;
		int m_clickEvent;
	};

}
#endif