#ifndef __GUI__H__
#define __GUI__H__

#include "PlayerType.h"

#include <irrlicht.h>
#include <iostream>
#include <sstream>
namespace Game
{
	/**
	 * @brief	This Class creates the graphical user interface element of the game	
	 *			
	 * @author	Bram van Elderen
	 */
	class Gui
	{
	
	public:
		enum GuiButton
		{
			BUTTON_STOP_GAME,
			BUTTON_MENU,
			BUTTON_CLEAR,
			BUTTON_ATTACKERS_TURN,
			BUTTON_BUY_PENCIL,
			BUTTON_CAPTURE_PENCILS,
			BUTTON_DEFENDERS_TURN,
			BUTTON_CREATE_TOWER,
			BUTTON_DELETE_TOWER,
			BUTTON_UPGRADE_TOWER_SPEED,
			BUTTON_UPGRADE_TOWER_RANGE,
			BUTTON_UPGRADE_TOWER_DAMAGE,
			BUTTON_CONTROLS_MENU,
			BUTTON_START_WAVE
		};
		
		/**
		 * @brief	Constructor
		 * @param	p_guienv A reference to the guienviroment given from the kernel.
		 */
		Gui(irr::gui::IGUIEnvironment* p_guienv);

		/**
		 * @brief	Destructor
		 */
		~Gui();

		/**
		 * @brief	This function is used to draw the gui elements that were added in the m_guienv.
		 * @param	UpdateGui uses p_wavetimer to display the time untill the next wave in the GUI
		 * @param	p_resources is used to display the resources available in the GUI
		 */
		void UpdateGui(int p_waveNumber, int p_waveSize, int p_creaturesSpawned,
				int p_fps,
				int p_player1Points, int p_player2Points);

		/**
		 *	@brief Creates the menu or destroys the menu
		 */
		void UpdateMenu();

		/**
		 *	@brief Creates the control menu or destroys the controls menu
		 */
		void UpdateControlsMenu();

		///@todo	Needs comments
		void Draw();

		/**
		 *	Clears all GUI elements
		 */
		void Clear();

		/**
		 * @brief	Properly destructs all the member properties
		 */
		void Cleanup();

		void endGame(int);

		void ShowVictory(PlayerType p_playerType);
		void HideVictory();

		void SetButtonAttackersTurnEnabled(bool p_state);
		void SetButtonAttackersActionsEnabled(bool p_state);
		void SetButtonDefendersTurnEnabled(bool p_state);
		void SetButtonDefendersActionsEnabled(bool p_state);
		void SetButtonStartWaveEnabled(bool p_state);

	private:
		irr::gui::IGUIEnvironment* m_guiEnvironment;
		irr::gui::IGUIImage* m_menu;
		irr::gui::IGUIImage* m_controls;
		irr::gui::IGUIImage* m_imageSidebar;
		irr::gui::IGUIImage* m_imageSidebarInfo;
		irr::gui::IGUIImage* m_imageVictory;
		irr::gui::IGUIStaticText* m_textAmountOfCreatures;
		irr::gui::IGUIStaticText* m_textWaveNumber;
		irr::gui::IGUIStaticText* m_textFps;
		irr::gui::IGUIStaticText* m_textPlayer1Points;
		irr::gui::IGUIStaticText* m_textPlayer2Points;

		irr::gui::IGUIButton* m_buttonAttackersTurn;
		irr::gui::IGUIButton* m_buttonBuyPencil;
		irr::gui::IGUIButton* m_buttonCapturePencils;
		irr::gui::IGUIButton* m_buttonDefendersTurn;
		irr::gui::IGUIButton* m_buttonCreateTower;
		irr::gui::IGUIButton* m_buttonDeleteTower;
		irr::gui::IGUIButton* m_buttonUpgradeTowerSpeed;
		irr::gui::IGUIButton* m_buttonUpgradeTowerRange;
		irr::gui::IGUIButton* m_buttonUpgradeTowerDamage;
		irr::gui::IGUIButton* m_buttonControlsMenu;
		irr::gui::IGUIButton* m_buttonStartWave;

		int m_screenWidth;
		int m_screenHeight;
		bool m_menuIsActive;
		bool m_controlsMenuIsActive;
		bool m_victoryIsActive;
		bool m_defeatSceenIsActive;

		void CreateGUIControls();

		/** 
		 * @brief Converts a string and an int to a wString so it can be used easily with Irrlicht
		 * @param The method gets an string and an int as input which get converted
		 */
		std::wstring stringToWString(std::string,int);
	};
}
#endif