#include "Game/Gui.h"

namespace Game
{
	Gui::Gui(irr::gui::IGUIEnvironment* p_guienv)
	{
		m_guiEnvironment = p_guienv;
		m_menu = NULL;
		m_menuControls = NULL;
		m_imageVictory = NULL;
		m_textAmountOfCreatures = NULL;
		m_textWaveNumber = NULL;
		m_textFps = NULL;
		m_textPlayer1Points = NULL;
		m_textPlayer2Points = NULL;
	 	m_buttonAttackersTurn = NULL;
		m_buttonBuyPencil = NULL;
		m_buttonCapturePencils = NULL;
		m_buttonDefendersTurn = NULL;
		m_buttonCreateTower = NULL;
		m_buttonDeleteTower = NULL;
		m_buttonUpgradeTowerSpeed = NULL;
		m_buttonUpgradeTowerRange = NULL;
		m_buttonUpgradeTowerDamage = NULL;
		m_buttonControlsMenu = NULL;
		m_buttonStartWave = NULL;
		
		const irr::core::dimension2d<irr::u32>& screenResolution = m_guiEnvironment->getVideoDriver()->getScreenSize();
		m_screenHeight = screenResolution.Height;
		m_screenWidth = screenResolution.Width;
		m_controlsMenuIsActive = false;
		m_victoryIsActive = false;
		m_defeatSceenIsActive= false;
		//getting screen resolution for placing buttons on the right place

		m_guiEnvironment->setSkin(m_guiEnvironment->createSkin(irr::gui::EGST_WINDOWS_CLASSIC));
		irr::gui::IGUISkin* skin = m_guiEnvironment->getSkin();
		irr::gui::IGUIFont* font = m_guiEnvironment->getFont("resources/textures/fontlucida.png");		
		if (font)
		{
			skin->setFont(font);
		}
		skin->setFont(m_guiEnvironment->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);

		//Making the GUI fully visible
		for (irr::u32 i=0; i<irr::gui::EGDC_COUNT; ++i)
		{
			irr::video::SColor color = m_guiEnvironment->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
			color.setAlpha(255);
			m_guiEnvironment->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, color);
		}

		CreateGUIControls();

		SetButtonAttackersTurnEnabled(true);
		SetButtonAttackersActionsEnabled(false);
		SetButtonDefendersTurnEnabled(false);
		SetButtonDefendersActionsEnabled(false);
		SetButtonStartWaveEnabled(false);
	}

	void Gui::UpdateGui(int p_waveNumber, int p_waveSize, int p_creaturesSpawned,
			int p_fps, int p_player1Points, int p_player2Points)
	{
		m_textAmountOfCreatures->setText(StringToWString("Creatures : ", p_creaturesSpawned).c_str());				
		m_textWaveNumber->setText(StringToWString("Wave : ", p_waveNumber).c_str());
		m_textFps->setText(StringToWString("FPS : ", p_fps).c_str());
		m_textPlayer1Points->setText(StringToWString("Player 1 Points : ", p_player1Points).c_str());
		m_textPlayer2Points->setText(StringToWString("Player 2 Points : ", p_player2Points).c_str());

		m_guiEnvironment->drawAll();
	}

	void Gui::ShowMenu()
	{
		if (m_menu == NULL)
		{
			m_menu = m_guiEnvironment->addImage(irr::core::recti((m_screenWidth / 2) - 100, (m_screenHeight / 2) - 100, 
					(m_screenWidth / 2) + 100, (m_screenHeight / 2) + 100));
			m_menu->setImage(m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/bar.png"));
			m_menu->setScaleImage(true);

			irr::gui::IGUIButton* returnButton = m_guiEnvironment->addButton(irr::core::recti(35, 65, 140, 80), 
					m_menu, BUTTON_HIDE_MENU, L"Return", L"Returns to the game");
			returnButton->setImage(m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/button.png"));
			returnButton->setScaleImage(true);

			irr::gui::IGUIButton* quitButton = m_guiEnvironment->addButton(irr::core::recti(35, 95, 140, 110),
					m_menu, BUTTON_STOP_GAME, L"Quit", L"Exits program");
			quitButton->setImage(m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/button.png"));
			quitButton->setScaleImage(true);
		}
	}

	void Gui::HideMenu()
	{
		if (m_menu != NULL)
		{
			m_menu->remove();
			m_menu = NULL;
		}
	}

	void Gui::ShowControlsMenu()
	{
		if (m_menuControls == NULL)
		{
			m_menuControls = m_guiEnvironment->addImage(irr::core::recti((m_screenWidth / 2) - 100, (m_screenHeight / 2) - 100, 
					(m_screenWidth / 2) + 100, (m_screenHeight / 2) + 100));
			m_menuControls->setImage(m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/bar.png"));
			m_menuControls->setScaleImage(true);
			m_guiEnvironment->addStaticText(L"F:Switch camera mode.", irr::core::recti(35, 35, 300, 50), false, true, m_menuControls);

			irr::gui::IGUIButton* returnButton = m_guiEnvironment->addButton(irr::core::recti(35, 65, 140, 80), 
					m_menuControls, BUTTON_HIDE_CONTROLS_MENU, L"Return", L"Returns to the game");
			returnButton->setImage(m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/button.png"));
			returnButton->setScaleImage(true);
		}
	}

	void Gui::HideControlsMenu()
	{
		if (m_menuControls != NULL)
		{
			m_menuControls->remove();
			m_menuControls = NULL;
		}
	}


	void Gui::ShowVictory(PlayerType p_playerType)
	{
		if (m_imageVictory == NULL)
		{
			irr::video::ITexture* image;
		
			if (p_playerType == PlayerType::TYPE_DEFENDER)
			{
				image = m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/victory.png");
			}
			else
			{
				image = m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/defeat.png");
			}
		
			m_imageVictory = m_guiEnvironment->addImage(irr::core::recti((m_screenWidth / 2) - 300,(m_screenHeight / 2) - 169,
					(m_screenWidth / 2) + 300, (m_screenHeight / 2) + 169), 0, 5);
			m_imageVictory->setImage(image);
			m_imageVictory->setScaleImage(true);
		}
	}

	void Gui::HideVictory()
	{
		if (m_imageVictory != NULL)
		{
			m_imageVictory->remove();
			m_imageVictory = NULL;
		}			
	}

	void Gui::SetButtonAttackersTurnEnabled(bool p_state)
	{
		m_buttonAttackersTurn->setEnabled(p_state);
	}

	void Gui::SetButtonAttackersActionsEnabled(bool p_state)
	{
		m_buttonBuyPencil->setEnabled(p_state);
		m_buttonCapturePencils->setEnabled(p_state);
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

	void Gui::CreateGUIControls()
	{

		//Initializing User Interface
		irr::video::ITexture* m_textureButton = m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/button.png");

		//Sidebar
		m_imageSidebar = m_guiEnvironment->addImage(m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/sidebar.png"),
				irr::core::position2d<int>(m_screenWidth - 200, 0));
		int midPositionSidebar = (m_imageSidebar->getAbsolutePosition().getWidth() / 2);
		
		int buttonHeight = 30;
		int buttonYOffset = 20;
		int buttonWidth = m_imageSidebar->getAbsolutePosition().getWidth() - 40;

		//Button Attackers Turn
		m_buttonAttackersTurn = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 10, 
				midPositionSidebar+  buttonWidth / 2, 40), m_imageSidebar, BUTTON_ATTACKERS_TURN, L"Attackers Turn");
		m_buttonAttackersTurn->setImage(m_textureButton);
		m_buttonAttackersTurn->setScaleImage(true);

		//Button Buy Pencil
		m_buttonBuyPencil = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 50, 
			midPositionSidebar + buttonWidth / 2, 80), m_imageSidebar, BUTTON_BUY_PENCIL, L"Buy Pencil");
		m_buttonBuyPencil->setImage(m_textureButton);
		m_buttonBuyPencil->setScaleImage(true);

		//Button Capture Pencils
		m_buttonCapturePencils = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar-buttonWidth/2, 90,
			midPositionSidebar+buttonWidth/2, 120), m_imageSidebar, BUTTON_CAPTURE_PENCILS, L"Capture Pencils");
		m_buttonCapturePencils->setImage(m_textureButton);
		m_buttonCapturePencils->setScaleImage(true);

		//Button Defenders Turn
		m_buttonDefendersTurn = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar-buttonWidth / 2, 130, midPositionSidebar + buttonWidth / 2, 
				160), m_imageSidebar, BUTTON_DEFENDERS_TURN, L"Defenders Turn");
		m_buttonDefendersTurn->setImage(m_textureButton);
		m_buttonDefendersTurn->setScaleImage(true);

		//Button Create Tower
		m_buttonCreateTower = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 170, midPositionSidebar + buttonWidth / 2, 200),
				m_imageSidebar, BUTTON_CREATE_TOWER, L"Create Tower");
		m_buttonCreateTower->setImage(m_textureButton);
		m_buttonCreateTower->setScaleImage(true);

		//Button Delete Tower
		m_buttonDeleteTower = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 210, 
				midPositionSidebar + buttonWidth / 2, 240), m_imageSidebar, BUTTON_DELETE_TOWER, L"Delete Tower");
		m_buttonDeleteTower->setImage(m_textureButton);
		m_buttonDeleteTower->setScaleImage(true);

		//Button Upgrade Tower Speed
		m_buttonUpgradeTowerSpeed = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 250, 
				midPositionSidebar + buttonWidth / 2, 280), m_imageSidebar, BUTTON_UPGRADE_TOWER_SPEED, L"Upgrade Tower Speed");
		m_buttonUpgradeTowerSpeed->setImage(m_textureButton);
		m_buttonUpgradeTowerSpeed->setScaleImage(true);

		//Button Upgrade Tower Range
		m_buttonUpgradeTowerRange = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 290, 
				midPositionSidebar + buttonWidth / 2, 320), m_imageSidebar, BUTTON_UPGRADE_TOWER_RANGE, L"Upgrade Tower Range");
		m_buttonUpgradeTowerRange->setImage(m_textureButton);
		m_buttonUpgradeTowerRange->setScaleImage(true);

		//Button Upgrade Tower Damage
		m_buttonUpgradeTowerDamage = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 330, 
				midPositionSidebar + buttonWidth / 2, 360), m_imageSidebar, BUTTON_UPGRADE_TOWER_RANGE, L"Upgrade Tower Damage");
		m_buttonUpgradeTowerDamage->setImage(m_textureButton);
		m_buttonUpgradeTowerDamage->setScaleImage(true);

		//Button Controls Menu
		m_buttonControlsMenu = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 410, 
				midPositionSidebar + buttonWidth / 2, 440), m_imageSidebar, BUTTON_SHOW_CONTROLS_MENU, L"Controls");
		m_buttonControlsMenu->setImage(m_textureButton);
		m_buttonControlsMenu->setScaleImage(true);

		//Button Start Wave
		m_buttonStartWave = m_guiEnvironment->addButton(irr::core::recti(midPositionSidebar - buttonWidth / 2, 450, 
				midPositionSidebar + buttonWidth / 2, 480), m_imageSidebar, BUTTON_START_WAVE, L"Start Wave");
		m_buttonStartWave->setImage(m_textureButton);
		m_buttonStartWave->setScaleImage(true);
		
		//Sidebar Info
		m_imageSidebarInfo = m_guiEnvironment->addImage(irr::core::recti(0, m_screenHeight - 130, 250, m_screenHeight - 20), m_imageSidebar);
		m_imageSidebarInfo->setImage(m_guiEnvironment->getVideoDriver()->getTexture("resources/textures/bar.png"));
		m_imageSidebarInfo->setScaleImage(true);

		//Sidebar Info Text
		irr::video::SColor textColor(255, 0, 0, 0);
		m_textAmountOfCreatures = m_guiEnvironment->addStaticText(L" ", irr::core::recti(10, 10, 400, 40), false, true, m_imageSidebarInfo);		
		m_textAmountOfCreatures->setOverrideColor(textColor);
		m_textWaveNumber = m_guiEnvironment->addStaticText(L" ", irr::core::recti(10, 30, 400, 60), false, true, m_imageSidebarInfo);
		m_textWaveNumber->setOverrideColor(textColor);
		m_textFps = m_guiEnvironment->addStaticText(L"FPS : ", irr::core::recti(10, 50, 400, 80), false, true, m_imageSidebarInfo);
		m_textFps->setOverrideColor(textColor);
		m_textPlayer1Points = m_guiEnvironment->addStaticText(L"PlayerHealth : ", irr::core::recti(10, 70, 400, 100), false, true, m_imageSidebarInfo);
		m_textPlayer1Points->setOverrideColor(textColor);
		m_textPlayer2Points = m_guiEnvironment->addStaticText(L"PlayerResources : ", irr::core::recti(10, 90, 400, 120), false, true, m_imageSidebarInfo);
		m_textPlayer2Points->setOverrideColor(textColor);
	}

	std::wstring Gui::StringToWString(std::string p_string, int p_int)
	{
		std::ostringstream tmpOstring;
		tmpOstring << p_int;
		p_string += tmpOstring.str();
		std::wstring tmpWstring(p_string.begin(), p_string.end());
		return tmpWstring;
	}
}