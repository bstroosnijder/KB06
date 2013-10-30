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
	 * @author	Bram van Elderen
	 * @todo	Check TODO's in Header.
	 */
	class EventHandler : public irr::IEventReceiver
	{
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
		 * @brief Constructor TODO
		 */
		EventHandler(UserInputListener* p_userInputListener,
				irr::IrrlichtDevice* p_device,
				Game::Gui* p_gui,
				Game::Playground* p_playground);
		
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
		UserInputListener* m_userInputListener;
		Game::Gui* m_gui;
		Game::Playground* m_playground;
		irr::IrrlichtDevice* m_device;
		int m_clickEvent;
	};

}
#endif