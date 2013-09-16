#include "Game/InputHandler.h"

namespace Game
{
	InputHandler::InputHandler()
	{
		m_listeners = Listeners();
	}

	InputHandler::~InputHandler()
	{
		Cleanup();
	}

	void InputHandler::Cleanup()
	{
		m_listeners.clear();
	}

	bool InputHandler::OnEvent(const irr::SEvent& p_evt)
	{
		Listeners::iterator it;
		for (it = m_listeners.begin(); it != m_listeners.end(); ++it)
		{
			(*it)->OnEvent(p_evt);
		}

		return false;
	}

	bool InputHandler::Contains(irr::IEventReceiver* p_listener)
	{
		return (std::find(m_listeners.begin(), m_listeners.end(), p_listener) != m_listeners.end());
	}

	void InputHandler::AddListener(irr::IEventReceiver* p_listener)
	{
		m_listeners.push_back(p_listener);
	}

	void InputHandler::RemoveListener(irr::IEventReceiver* p_listener)
	{
		m_listeners.remove(p_listener);
	}
}