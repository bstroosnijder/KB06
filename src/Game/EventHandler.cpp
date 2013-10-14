#include "Game/EventHandler.h"

namespace Game
{
	EventHandler::EventHandler(irr::IrrlichtDevice* p_device, Game::Gui* p_gui, Game::Playground* p_playground)
	{
		m_gui = p_gui;
		m_device = p_device;
		m_playground = p_playground;
		clickEvent = NULL;
	}

	EventHandler::~EventHandler()
	{
		Cleanup();
	}

	bool EventHandler::OnEvent(const irr::SEvent& event)
	{
		if (event.EventType == irr::EET_GUI_EVENT)
		{
			irr::s32 id = event.GUIEvent.Caller->getID();
			if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
			{			
				if (id == MENU_BUTTON)
				{
					m_gui->UpdateMenu();
					return true;
				}					
				if (id == QUIT_BUTTON)
				{
					m_device->closeDevice();
					return true;
				}
				if (id == ClEAR_BUTTON)
				{
					m_gui->Clear();
					return true;
				}
				if (id == TOWER_BUTTON)
				{
					clickEvent = ClickEvent::TOWER_PRESSED;
					return true;
				}
				if (id == SELL_BUTTON)
				{
					clickEvent = ClickEvent::SELL_PRESSED;
					return true;
				}
				if (id == CONTROLS_BUTTON)
				{
					m_gui->UpdateControlsMenu();
					return true;
				}
				if (id == STARTGAME_BUTTON)
				{
					m_playground->StartNextWave();
					return true;
				}
			}
		}

		if (event.EventType ==irr::EET_KEY_INPUT_EVENT)
		{
			irr::s32 keyInput = event.KeyInput.Key;
			
			if (keyInput == irr::KEY_ESCAPE && !event.KeyInput.PressedDown)
			{
				m_gui->UpdateMenu();
				return true;
			}
			if (keyInput == irr::KEY_KEY_F && !event.KeyInput.PressedDown)
			{
				//Enables/disables input for the camera scene node
				if (m_device->getSceneManager()->getActiveCamera()->isInputReceiverEnabled())
				{
					m_device->getCursorControl()->setVisible(true);
					m_device->getSceneManager()->getActiveCamera()->setInputReceiverEnabled(false);
				}
				else if (!m_device->getSceneManager()->getActiveCamera()->isInputReceiverEnabled())
				{
					m_device->getCursorControl()->setVisible(false);
					m_device->getSceneManager()->getActiveCamera()->setInputReceiverEnabled(true);
				}
				return true;
			}			
		}
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			if (event.MouseInput.isLeftPressed())
			{
				if (clickEvent == ClickEvent::TOWER_PRESSED)
				{
					
					irr::core::vector2d<irr::s32> mousePosition = m_device->getCursorControl()->getPosition();
					m_playground->SpawnTower(mousePosition);
					clickEvent = NULL;
					return true;
				}
				if (clickEvent == ClickEvent::SELL_PRESSED)
				{

					irr::core::vector2d<irr::s32> mousePosition = m_device->getCursorControl()->getPosition();
					m_playground->SellTower(mousePosition);
					clickEvent = NULL;
					return true;
				}	
			}				
		}

		return false;
	}

	void EventHandler::Cleanup()
	{
		delete m_gui;
		delete m_device;
	}
}	