#ifndef __EventHandler__H__
#define __EventHandler__H__

#include "UserInputListener.h"
#include "Game/Gui.h"
#include "Game/Playground.h"

#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	This Class creates handles incoming events from different inputs.
	 *			
	 * @author	Bram van Elderen.
	 * @author	Michel van Os.
	 */
	class EventHandler : public irr::IEventReceiver
	{
		/**
		 * @brief	Click events used by the EventHandler to store what 
		 *			GUI butten is pressed.
		 *
		 *			The GUI button must be followed by a
		 *			mouse click on the playground to finish the event. For example.
		 *			When the GUI button Create Tower is clicked the variable m_clickEvent
		 *			will be set to ClickEvent::CREATE_TOWER. When the player now clicks
		 *			with the mouse on the playground a Tower will be created.
		 * @author	Michel van Os.
		 */
		enum ClickEvent
		{
			CREATE_TOWER = 1,
			DELETE_TOWER,
			UPGRADE_TOWER_SPEED,
			UPGRADE_TOWER_RANGE,
			UPGRADE_TOWER_DAMAGE
		};

	public:
		
		/**
		 * @todo Constructor TODO
		 */
		EventHandler(UserInputListener* p_userInputListener,
				irr::IrrlichtDevice* p_device,
				Game::Gui* p_gui,
				Game::Playground* p_playground);
		
		/**
		 * @brief Destructor
		 */
		~EventHandler();

		/**
		 * @brief	Handles GUI, mouse and keyboard events.
		 *
		 * @author	Bram van Elderen.
		 * @author	Michel van Os.
		 * @param	p_event The irr::SEvent which contains all information about
		 *			the triggered event.
		 * @return	Returns whether the event has been handled by the EventHandler.
		 *
		 */
		virtual bool OnEvent(const irr::SEvent& p_event);

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();

	private:
		UserInputListener* m_userInputListener;
		Game::Gui* m_gui;
		Game::Playground* m_playground;
		irr::IrrlichtDevice* m_device;
		int m_clickEvent;
	};

}
#endif