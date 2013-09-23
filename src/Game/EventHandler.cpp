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
		
		m_event = &event;
		std::cout << event.EventType;
		irr::gui::IGUIEnvironment* env = m_device->getGUIEnvironment();
		if (event.EventType == irr::EET_GUI_EVENT)
		{
			irr::s32 id = event.GUIEvent.Caller->getID();
			switch(event.GUIEvent.EventType)
			{
			case irr::gui::EGET_BUTTON_CLICKED:
				if (id == MENU_BUTTON)
				{
					irr::gui::IGUIWindow* menu = env->addWindow(
					irr::core::rect<irr::s32>(200, 200, 400, 300),
					false, // modal?
					L"Menu");
					return true;
				}					
				if (id == QUIT_BUTTON)
				{
					m_device->closeDevice();
					return true;
				}				
				break;
			}
			return false;
		}
		if (event.EventType ==irr::EET_KEY_INPUT_EVENT)
		{
			irr::s32 keyInput = event.KeyInput.Key;
			if (keyInput == irr::KEY_ESCAPE)
			{
				irr::gui::IGUIWindow* menu = env->addWindow(
					irr::core::rect<irr::s32>(200, 200, 400, 300),
					false, // modal?
					L"Menu");
				env->addButton(irr::core::rect<irr::s32>(35,35,140,50),menu, 101,L"Quit", L"Exits program");

				return true;
			}
			return false;
		}
		return false;
	}
}	