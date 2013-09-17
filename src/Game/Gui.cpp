#include "Game/Gui.h"

namespace Game
{
	Gui::Gui(irr::gui::IGUIEnvironment* p_guienv)
	{
		m_guienv = p_guienv;
		m_guienv->addStaticText(L"Tower Defense", irr::core::rect<irr::s32>(10,10,260,22), true);
		exitButton = m_guienv->addButton(irr::core::rect<irr::s32>(10,240,110,240 + 32), 0, 101,L"Quit", L"Exits Program");	
		irr::gui::IGUIStaticText* text;
		//text->setToolTipText(L"hey");
		//text->setAlignment(irr::gui::EGUIA_LOWERRIGHT, irr::gui::EGUIA_LOWERRIGHT, irr::gui::EGUIA_UPPERLEFT, irr::gui::EGUIA_UPPERLEFT);
	}

	void Gui::drawGui()
	{
		m_guienv->drawAll();
	}

	bool Gui::exitButtonPressed()
	{
		if (exitButton->isPressed())
		{
			return true;
		}
		return false;
	}
}