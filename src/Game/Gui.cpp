#include "Game/Gui.h"

namespace Game
{
	Gui::Gui(irr::gui::IGUIEnvironment* p_guienv)
	{
		m_guienv = p_guienv;
		m_menu = NULL;
		m_controls = NULL;
		m_amountOfCreatures = NULL;
		m_waveNumber = NULL;
		m_fps = NULL;
		m_playerHealth = NULL;
		m_playerResources = NULL;
		
		const irr::core::dimension2d<irr::u32>& screenResolution = m_guienv->getVideoDriver()->getScreenSize();
		m_screenHeight = screenResolution.Height;
		m_screenWidth = screenResolution.Width;
		m_menuIsActive = false;
		m_controlsMenuIsActive = false;
		m_victoryIsActive = false;
		m_defeatSceenIsActive= false;
		//getting screen resolution for placing buttons on the right place

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

		CreateGUIControls();

		SetButtonAttackersTurnEnabled(true);
		SetButtonAttackersActionsEnabled(false);
		SetButtonDefendersTurnEnabled(false);
		SetButtonDefendersActionsEnabled(false);
		SetButtonStartWaveEnabled(false);
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
			m_menu = m_guienv->addImage(irr::core::rect<irr::s32>((m_screenWidth/2)-100, (m_screenHeight/2)-100, (m_screenWidth/2)+100, (m_screenHeight/2)+100));
			m_menu->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/bar.png"));
			m_menu->setScaleImage(true);

			irr::gui::IGUIButton* returnButton = m_guienv->addButton(irr::core::rect<irr::s32>(35,65,140,80), m_menu, BUTTON_MENU,L"Return", L"Returns to the game");
			returnButton->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/button.png"));
			returnButton->setScaleImage(true);

			irr::gui::IGUIButton* quitButton = m_guienv->addButton(irr::core::rect<irr::s32>(35,95,140,110), m_menu, BUTTON_STOP_GAME,L"Quit", L"Exits program");
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

			irr::gui::IGUIButton* returnButton = m_guienv->addButton(irr::core::rect<irr::s32>(35,65,140,80),m_controls, BUTTON_CONTROLS_MENU,L"Return", L"Returns to the game");
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

	void Gui::SetButtonAttackersTurnEnabled(bool p_state)
	{
		m_buttonAttackersTurn->setEnabled(p_state);
	}

	void Gui::SetButtonAttackersActionsEnabled(bool p_state)
	{
		m_buttonBuyPencil->setEnabled(p_state);
	}

	void Gui::SetButtonDefendersTurnEnabled(bool p_state)
	{
		m_buttonDefendersTurn->setEnabled(p_state);
	}

	void Gui::SetButtonDefendersActionsEnabled(bool p_state)
	{
		m_buttonCreateTower->setEnabled(p_state);
		m_buttonDeleteTower->setEnabled(p_state);
		m_buttonUpgradeTowerSpeed->setEnabled(p_state);
		m_buttonUpgradeTowerRange->setEnabled(p_state);
		m_buttonUpgradeTowerDamage->setEnabled(p_state);
	}

	void Gui::SetButtonStartWaveEnabled(bool p_state)
	{
		m_buttonStartWave->setEnabled(p_state);
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

	void Gui::CreateGUIControls()
	{

		//Initializing User Interface
		irr::video::ITexture* m_textureButton = m_guienv->getVideoDriver()->getTexture("resources/textures/button.png");

		//Sidebar
		irr::gui::IGUIImage* sideBar = m_guienv->addImage(m_guienv->getVideoDriver()->getTexture("resources/textures/sidebar.png"),irr::core::position2d<int>(m_screenWidth-200,0));
		int midPositionSidebar = (sideBar->getAbsolutePosition().getWidth()/2);
		
		int buttonHeight = 30;
		int buttonWidth = sideBar->getAbsolutePosition().getWidth() - 40;

		//Button Attackers Turn
		m_buttonAttackersTurn = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 10, midPositionSidebar+buttonWidth/2, 40), sideBar, BUTTON_ATTACKERS_TURN, L"Attackers Turn");
		m_buttonAttackersTurn->setImage(m_textureButton);
		m_buttonAttackersTurn->setScaleImage(true);

		//Button Buy Pencil
		m_buttonBuyPencil = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 50, midPositionSidebar+buttonWidth/2, 80), sideBar, BUTTON_BUY_PENCIL, L"Buy Pencil");
		m_buttonBuyPencil->setImage(m_textureButton);
		m_buttonBuyPencil->setScaleImage(true);

		//Button Defenders Turn
		m_buttonDefendersTurn = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 130, midPositionSidebar+buttonWidth/2, 160), sideBar, BUTTON_DEFENDERS_TURN, L"Defenders Turn");
		m_buttonDefendersTurn->setImage(m_textureButton);
		m_buttonDefendersTurn->setScaleImage(true);

		//Button Create Tower
		m_buttonCreateTower = m_guienv->addButton(irr::core::recti(midPositionSidebar-buttonWidth/2, 170, midPositionSidebar+buttonWidth/2, 200), sideBar, BUTTON_CREATE_TOWER, L"Create Tower");
		m_buttonCreateTower->setImage(m_textureButton);
		m_buttonCreateTower->setScaleImage(true);

		//Button Delete Tower
		m_buttonDeleteTower = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 210, midPositionSidebar+buttonWidth/2, 240), sideBar, BUTTON_DELETE_TOWER, L"Delete Tower");
		m_buttonDeleteTower->setImage(m_textureButton);
		m_buttonDeleteTower->setScaleImage(true);

		//Button Upgrade Tower Speed
		m_buttonUpgradeTowerSpeed = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 250, midPositionSidebar+buttonWidth/2, 280), sideBar, BUTTON_UPGRADE_TOWER_SPEED, L"Upgrade Tower Speed");
		m_buttonUpgradeTowerSpeed->setImage(m_textureButton);
		m_buttonUpgradeTowerSpeed->setScaleImage(true);

		//Button Upgrade Tower Range
		m_buttonUpgradeTowerRange = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 290, midPositionSidebar+buttonWidth/2, 320), sideBar, BUTTON_UPGRADE_TOWER_RANGE, L"Upgrade Tower Range");
		m_buttonUpgradeTowerRange->setImage(m_textureButton);
		m_buttonUpgradeTowerRange->setScaleImage(true);

		//Button Upgrade Tower Damage
		m_buttonUpgradeTowerDamage = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 330, midPositionSidebar+buttonWidth/2, 360), sideBar, BUTTON_UPGRADE_TOWER_RANGE, L"Upgrade Tower Damage");
		m_buttonUpgradeTowerDamage->setImage(m_textureButton);
		m_buttonUpgradeTowerDamage->setScaleImage(true);

		//Button Controls Menu
		m_buttonControlsMenu = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 410, midPositionSidebar+buttonWidth/2, 440), sideBar, BUTTON_CONTROLS_MENU,L"Controls");
		m_buttonControlsMenu->setImage(m_textureButton);
		m_buttonControlsMenu->setScaleImage(true);

		//Button Start Wave
		m_buttonStartWave = m_guienv->addButton(irr::core::rect<irr::s32>(midPositionSidebar-buttonWidth/2, 450, midPositionSidebar+buttonWidth/2, 480), sideBar, BUTTON_START_WAVE, L"Start Wave");
		m_buttonStartWave->setImage(m_textureButton);
		m_buttonStartWave->setScaleImage(true);
		
		//Sidebar Info
		irr::gui::IGUIImage* sidebarInfo = m_guienv->addImage(irr::core::rect<irr::s32>(0,m_screenHeight-130,250,m_screenHeight-20),sideBar);
		sidebarInfo->setImage(m_guienv->getVideoDriver()->getTexture("resources/textures/bar.png"));
		sidebarInfo->setScaleImage(true);

		m_amountOfCreatures = m_guienv->addStaticText(L" ",irr::core::rect<irr::s32>(10,10,400,40),false,true,sidebarInfo);		
		m_amountOfCreatures->setOverrideColor(irr::video::SColor(255,0,0,0));
		m_waveNumber = m_guienv->addStaticText(L" ",irr::core::rect<irr::s32>(10,30,400,60),false,true,sidebarInfo);
		m_waveNumber->setOverrideColor(irr::video::SColor(255,0,0,0));
		m_fps = m_guienv->addStaticText(L"FPS : ",irr::core::rect<irr::s32>(10,50,400,80),false,true,sidebarInfo);
		m_fps->setOverrideColor(irr::video::SColor(255,0,0,0));
		m_playerHealth = m_guienv->addStaticText(L"PlayerHealth : ",irr::core::rect<irr::s32>(10,70,400,100),false,true,sidebarInfo);
		m_playerHealth->setOverrideColor(irr::video::SColor(255,0,0,0));
		m_playerResources = m_guienv->addStaticText(L"PlayerResources : ",irr::core::rect<irr::s32>(10,90,400,120),false,true,sidebarInfo);
		m_playerResources->setOverrideColor(irr::video::SColor(255,0,0,0));
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