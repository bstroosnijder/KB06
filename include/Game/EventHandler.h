#ifndef __EventHandler__H__
#define __EventHandler__H__

#include <irrlicht.h>

namespace Game
{
	enum
	{
		QUIT_BUTTON = 101,
		MENU_BUTTON = 102
	};
	
	
	/**
	 * @brief	This Class creates handles incoming events from the graphical user interface.
	 *			
	 * @author	Bram van Elderen
	 */
	class EventHandler	:	public irr::IEventReceiver
	{
	public:
		
		/**
		 * @brief Constructor
		 */
		EventHandler(irr::IrrlichtDevice* p_device);
		
		/**
		 * @brief Deconstructor
		 */
		~EventHandler();

		/**
		 *	@brief handles events
		 */
		virtual bool OnEvent(const irr::SEvent& event);

		/**
		 *	@brief returns event
		 */
		const irr::SEvent* getEvent();


	private:
		irr::IrrlichtDevice* m_device;
		const irr::SEvent* m_event;

	};

}
#endif