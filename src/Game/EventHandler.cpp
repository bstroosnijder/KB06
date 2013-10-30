#include "Game/EventHandler.h"

namespace Game
{
	EventHandler::EventHandler(UserInputListener* p_userInputListener,
			irr::IrrlichtDevice* p_device,
			Game::Gui* p_gui,
			Game::Playground* p_playground)
	{
		m_userInputListener = p_userInputListener;
		m_gui = p_gui;
		m_device = p_device;
		m_playground = p_playground;
		m_clickEvent = NULL;
	}

	EventHandler::~EventHandler()
	{
		Cleanup();
	}

	bool EventHandler::OnEvent(const irr::SEvent& p_event)
	{
		if (p_event.EventType == irr::EET_GUI_EVENT)
		{
			irr::s32 id = p_event.GUIEvent.Caller->getID();
			if (p_event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
			{
				switch (id)
				{
				case Gui::BUTTON_MENU:
					m_gui->UpdateMenu();
					return true;

				case Gui::BUTTON_STOP_GAME:
					m_userInputListener->OnStopGame();
					return true;
				
				case Gui::BUTTON_CLEAR:
					m_gui->Clear();
					return true;

				case Gui::BUTTON_ATTACKERS_TURN:
					m_userInputListener->OnPlacePencils();
					return true;

				case Gui::BUTTON_BUY_PENCIL:
					m_userInputListener->OnBuyPencil();
					return true;

				case Gui::BUTTON_CAPTURE_PENCILS:
					m_userInputListener->OnCapturePencils();
					break;

				case Gui::BUTTON_DEFENDERS_TURN:
					m_userInputListener->OnPlaceTowers();
					return true;
				
				case Gui::BUTTON_CREATE_TOWER:
					m_clickEvent = ClickEvent::CREATE_TOWER;
					return true;

				case Gui::BUTTON_DELETE_TOWER:
					m_clickEvent = ClickEvent::DELETE_TOWER;
					return true;

				case Gui::BUTTON_UPGRADE_TOWER_SPEED:
					m_clickEvent = ClickEvent::UPGRADE_TOWER_SPEED;
					return true;

				case Gui::BUTTON_UPGRADE_TOWER_RANGE:
					m_clickEvent = ClickEvent::UPGRADE_TOWER_DAMAGE;
					return true;

				case Gui::BUTTON_UPGRADE_TOWER_DAMAGE:
					m_clickEvent = ClickEvent::UPGRADE_TOWER_DAMAGE;
					return true;

				case Gui::BUTTON_CONTROLS_MENU:
					m_gui->UpdateControlsMenu();
					return true;

				case Gui::BUTTON_START_WAVE:
					m_userInputListener->OnStartWave();
					return true;
				}
			}
		}
		else if (p_event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			irr::s32 keyInput = p_event.KeyInput.Key;
			
			if (keyInput == irr::KEY_ESCAPE && !p_event.KeyInput.PressedDown)
			{
				m_gui->UpdateMenu();
				return true;
			}
			if (keyInput == irr::KEY_KEY_F && !p_event.KeyInput.PressedDown)
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
		else if (p_event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			if (p_event.MouseInput.isLeftPressed())
			{
				switch (m_clickEvent)
				{
				case ClickEvent::CREATE_TOWER:
					m_userInputListener->OnTowerCreate(m_device->getCursorControl()->getPosition());
					m_clickEvent = NULL;
					return true;

				case ClickEvent::DELETE_TOWER:
					m_userInputListener->OnTowerDestroy(m_device->getCursorControl()->getPosition());
					//m_clickEvent = NULL;
					return true;

				case ClickEvent::UPGRADE_TOWER_SPEED:
					m_userInputListener->OnTowerUpgradeSpeed(m_device->getCursorControl()->getPosition());
					m_clickEvent = NULL;
					return true;

				case ClickEvent::UPGRADE_TOWER_RANGE:
					m_userInputListener->OnTowerUpgradeRange(m_device->getCursorControl()->getPosition());
					m_clickEvent = NULL;
					return true;

				case ClickEvent::UPGRADE_TOWER_DAMAGE:
					m_userInputListener->OnTowerUpgradeDamage(m_device->getCursorControl()->getPosition());
					m_clickEvent = NULL;
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