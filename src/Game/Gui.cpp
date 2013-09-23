#include "Game/Gui.h"

namespace Game
{
	Gui::Gui(irr::gui::IGUIEnvironment* p_guienv)
	{
		m_guienv = p_guienv;
		//m_guienv->addStaticText(L"Tower Defense", irr::core::rect<irr::s32>(10,10,260,22), true);
		//rect = (left position,top position,right position,bottom position)
		//exitButton = m_guienv->addButton(irr::core::rect<irr::s32>(200,20,500,40), 0, 101,L"Quit", L"Exits Program");	
		//menuButton = m_guienv->addButton(irr::core::rect<irr::s32>(10,200,40,240), 0, 102,L"Menu", L"Opens Menu");
		//m_guienv->addScrollBar(true,irr::core::rect<irr::s32>())
	}

	void Gui::drawGui()
	{
		m_guienv->drawAll();
	}
}