#ifndef __EventHandler__H__
#define __EventHandler__H__

#include <irrlicht.h>

namespace Game
{
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
		EventHandler(irr::IrrlichtDevice* p_device,irr::s32 p_counter, irr::gui::IGUIListBox* p_listbox);
		
		/**
		 * @brief Deconstructor
		 */
		~EventHandler();

		/**
		 *	@brief handles events
		 */
		virtual bool OnEvent(const irr::SEvent& event);



	private:
		irr::IrrlichtDevice* m_device;
		irr::s32 m_counter;
		irr::gui::IGUIListBox* m_listbox;
	};

}
#endif