#include "Game/Gui.h"

namespace Game
{
	Gui::Gui(irr::gui::IGUIEnvironment* p_guienv)
	{
		m_guienv = p_guienv;
		m_menuIsActive = false;
		m_controlsMenuIsActive = false;
		m_victoryIsActive = false;
		m_defeatSceenIsActive= false;
		//getting screen resolution for placing buttons on the right place
		const irr::core::dimension2d<irr::u32>& screenResolution = m_guienv->getVideoDriver()->getScreenSize();
		m_screenHeight = screenResolution.Height;
		m_screenWidth = screenResolution.Width;

		m_guienv->setSkin(m_guienv->createSkin(irr::gui::EGST_WINDOWS_CLASSIC));
		irr::gui::IGUISkin* skin = m_guienv->getSkin();
		irr::gui::IGUIFont* font = m_guienv->getFont("resources/textures/fontlucida.png");		
		if (font)
		{
			skin->setFont(font);
		}
		skin->setFont(m_guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);

		//Making the GUI fully visible
		for (irr::u32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
		{
			irr::video::SColor color = m_guienv->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
			color.setAlpha(255);
			m_guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, color);
		}

		//initializing user interface		
		irr::gui::IGUIImage* sideBar = m_guienv->addImage(m_guienv->getVideoDriver()->getTexture("resources/textures/sidebar.png"),irr::core::position2d<int>(m_screenWidth-200,0));
		int midPositionSidebar = (sideBar->getAbsolutePosition().getWidth()/2);

		irr::gui::IGUIButton* tower = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-40,10,midPositionSidebar+40,40),sideBar,TOWER_BUTTON,L"Tower");
		tower->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/button.png"));
		tower->setScaleImage(true);

		irr::gui::IGUIButton* sell = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-40,50,midPositionSidebar+40,80),sideBar,SELL_BUTTON,L"Sell");
		sell->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/button.png"));
		sell->setScaleImage(true);

		irr::gui::IGUIButton* controls = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-40,90,midPositionSidebar+40,120),sideBar,CONTROLS_BUTTON,L"Controls");
		controls->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/button.png"));
		controls->setScaleImage(true);

		irr::gui::IGUIButton* startGame = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-40,130,midPositionSidebar+40,160),sideBar,STARTGAME_BUTTON,L"Start game");
		startGame->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/button.png"));
		startGame->setScaleImage(true);

		irr::gui::IGUIImage* image = m_guienv->addImage(irr::core::rect<irr::s32>(0,m_screenHeight-130,250,m_screenHeight-20),sideBar);
		image->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/bar.png"));
		image->setScaleImage(true);
		m_amountOfCreatures = m_guienv->addStaticText(L" ",irr::core::rect<irr::s32>(10,10,400,40),false,true,image);		
		m_amountOfCreatures->setOverrideColor(irr::video::SColor(255,0,0,0));
		m_waveNumber = m_guienv->addStaticText(L" ",irr::core::rect<irr::s32>(10,30,400,60),false,true,image);
		m_waveNumber->setOverrideColor(irr::video::SColor(255,0,0,0));
		m_fps = m_guienv->addStaticText(L"FPS : ",irr::core::rect<irr::s32>(10,50,400,80),false,true,image);
		m_fps->setOverrideColor(irr::video::SColor(255,0,0,0));
		m_playerHealth = m_guienv->addStaticText(L"PlayerHealth : ",irr::core::rect<irr::s32>(10,70,400,100),false,true,image);
		m_playerHealth->setOverrideColor(irr::video::SColor(255,0,0,0));
		m_playerResources = m_guienv->addStaticText(L"PlayerResources : ",irr::core::rect<irr::s32>(10,90,400,120),false,true,image);
		m_playerResources->setOverrideColor(irr::video::SColor(255,0,0,0));
	}

	Gui::~Gui()
	{
		Cleanup();
	}

	void Gui::UpdateGui(int p_waveNumber, int p_AmountOfCreatures, int p_fps, int p_playerHealth, int p_resources)
	{


		//STRING CONVERSIE
		m_amountOfCreatures->setText(stringToWString("Creatures : ", p_AmountOfCreatures).c_str());				
		m_waveNumber->setText(stringToWString("Wave : ", p_waveNumber).c_str());
		m_fps->setText(stringToWString("FPS : ", p_fps).c_str());
		m_playerHealth->setText(stringToWString("Player Health : ", p_playerHealth).c_str());
		m_playerResources->setText(stringToWString("Player Resources : ", p_resources).c_str());

		m_guienv->drawAll();
	}

	void Gui::UpdateMenu()
	{
		//rect = (left position,top position,right position,bottom position)
		if (!m_menuIsActive)
		{			
			m_menu = m_guienv->addImage(irr::core::rect<irr::s32>((m_screenWidth/2)-100,(m_screenHeight/2)-100,(m_screenWidth/2)+100,(m_screenHeight/2)+100));
			m_menu->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/bar.png"));
			m_menu->setScaleImage(true);

			irr::gui::IGUIButton* returnButton = m_guienv->addButton(irr::core::rect<irr::s32>(35,65,140,80),m_menu, MENU_BUTTON,L"Return", L"Returns to the game");
			returnButton->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/button.png"));
			returnButton->setScaleImage(true);

			irr::gui::IGUIButton* quitButton = m_guienv->addButton(irr::core::rect<irr::s32>(35,95,140,110),m_menu, QUIT_BUTTON,L"Quit", L"Exits program");
			quitButton->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/button.png"));
			quitButton->setScaleImage(true);

			m_menuIsActive = true;
		}
		else if (m_menuIsActive)
		{
			m_menu->remove();
			m_menuIsActive = false;
		}

	}

	void Gui::UpdateControlsMenu()
	{
		//rect = (left position,top position,right position,bottom position)
		if (!m_controlsMenuIsActive)
		{
			m_controls = m_guienv->addImage(irr::core::rect<irr::s32>((m_screenWidth/2)-100,(m_screenHeight/2)-100,(m_screenWidth/2)+100,(m_screenHeight/2)+100));
			m_controls->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/bar.png"));
			m_controls->setScaleImage(true);
			m_guienv->addStaticText(L"F:Switch camera mode.",irr::core::rect<irr::s32>(35,35,300,50),false,true,m_controls);

			irr::gui::IGUIButton* returnButton = m_guienv->addButton(irr::core::rect<irr::s32>(35,65,140,80),m_controls, CONTROLS_BUTTON,L"Return", L"Returns to the game");
			returnButton->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/button.png"));
			returnButton->setScaleImage(true);

			m_controlsMenuIsActive = true;
		}
		else if (m_controlsMenuIsActive)
		{
			m_controls->remove();
			m_controlsMenuIsActive = false;
		}
	}

	void Gui::endGame(int p_endGame)
	{		
		if (p_endGame == 4)
		{
			if (m_victoryIsActive == false)
			{
				irr::gui::IGUIImage* victory = m_guienv->addImage(irr::core::rect<irr::s32>((m_screenWidth/2)-300,(m_screenHeight/2)-169,(m_screenWidth/2)+300,(m_screenHeight/2)+169),0,5);
				victory->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/victory.png"));
				victory->setScaleImage(true);
				m_victoryIsActive = true;
			}
		}
		if (p_endGame == 1)
		{
			if (m_defeatSceenIsActive == false)
			{
				irr::gui::IGUIImage* defeat = m_guienv->addImage(irr::core::rect<irr::s32>((m_screenWidth/2)-300,(m_screenHeight/2)-169,(m_screenWidth/2)+300,(m_screenHeight/2)+169),0,5);
				defeat->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/defeat.png"));
				defeat->setScaleImage(true);
				m_defeatSceenIsActive = true;
			}
		}
	}

	void Gui::Clear()
	{
		m_guienv->clear();		
	}

	void Gui::Cleanup()
	{
		delete m_guienv;
		delete m_menu;
		delete m_controls;
		delete m_waveNumber;
		delete m_amountOfCreatures;
	}

	std::wstring Gui::stringToWString(std::string p_string,int p_int)
	{
		std::ostringstream tmpOstring;
		tmpOstring <<p_int;
		p_string += tmpOstring.str();
		std::wstring tmpWstring(p_string.begin(), p_string.end());
		return tmpWstring;
	}
}