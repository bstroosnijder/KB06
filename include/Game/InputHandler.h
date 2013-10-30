#ifndef __GAME__INPUTHANDLER__H__
#define __GAME__INPUTHANDLER__H__

#include <irrlicht.h>
#include <list>

namespace Game
{
	/**
	 * @brief	TODO
	 *			
	 * @author	Alex Hodes
	 */
	class InputHandler : public irr::IEventReceiver
	{
	public:
		/**
		 * @brief	Constructor
		 */
		InputHandler();

		/**
		 * @brief	Destructor
		 */
		~InputHandler();

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();

		/**
		 * @brief	Handles events from irrlicht and distributes them amoun it's listeners
		 *
		 * @param	p_event The event received
		 * @return	Has the event been completely handled
		 */
		bool OnEvent(const irr::SEvent& p_event);

		/**
		 * @brief	Checks if p_listener is contained in our listeners list
		 *
		 * @param	p_listener The listener to check for
		 * @return	If it contains the listener
		 */
		bool Contains(irr::IEventReceiver* p_listener);

		/**
		 * @brief	Adds a listener to the list
		 *
		 * @param	p_listener The listener to add
		 */
		void AddListener(irr::IEventReceiver* p_listener);

		/**
		 * @brief	Removes a listener from the list
		 *
		 * @param	p_listener The listener to remove
		 */
		void RemoveListener(irr::IEventReceiver* p_listener);

	private:
		typedef std::list<irr::IEventReceiver*> Listeners;
		Listeners m_listeners;
	};
}

#endif