#include "Game/EventHandler.h"
#include <iostream>
namespace Game
{
	EventHandler::EventHandler(irr::IrrlichtDevice* p_device)
	{ 
		m_device = p_device;
	}

	EventHandler::~EventHandler()
	{
	}

	bool EventHandler::OnEvent(const irr::SEvent& event)
	{
		std::cout << event.EventType;
		if (event.EventType == irr::EET_GUI_EVENT)
		{
			irr::s32 id = event.GUIEvent.Caller->getID();
			irr::gui::IGUIEnvironment* env = m_device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
			case irr::gui::EGET_BUTTON_CLICKED:
				if (id == 102)
				{
					irr::gui::IGUIWindow* menu = env->addWindow(
					irr::core::rect<irr::s32>(200, 200, 400, 300),
					false, // modal?
					L"Menu");
				}					
				if (id == 101)
				{
					m_device->closeDevice();
				}						
			break;
			}			
		}
		return true;
	}

}	