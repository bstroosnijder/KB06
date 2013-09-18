#include "Game/EventHandler.h"

namespace Game
{
	EventHandler::EventHandler(irr::IrrlichtDevice* p_device,irr::s32 p_counter, irr::gui::IGUIListBox* p_listbox)
	{
		m_device = p_device;
		m_counter = p_counter;
		m_listbox = p_listbox;
	}

	EventHandler::~EventHandler()
	{
	}

	bool EventHandler::OnEvent(const irr::SEvent& event)
	{
		if (event.EventType == irr::EET_GUI_EVENT)
		{
			irr::s32 id = event.GUIEvent.Caller->getID();
			irr::gui::IGUIEnvironment* env = m_device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
			case irr::gui::EGET_BUTTON_CLICKED:
					switch (id)
					{
					case 102:
						//irr::gui::IGUIWindow* menu = 
					break;
					}
			break;
			}			
		}
		return true;
	}

}	