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
		EventHandler(irr::IrrlichtDevice* p_device);
		
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
	};

}
#endif