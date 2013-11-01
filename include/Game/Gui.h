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
	 * @author	Michel van Os.
	 */
	class Gui
	{
	
	public:
		/**
		 * @brief	GuiButton is used by the EventHandler to determine
		 *			which IGUIButton is pressed.
		 *
		 * @author	Michel van Os.
		 */
		enum GuiButton
		{
			BUTTON_STOP_GAME,
			BUTTON_HIDE_MENU,
			BUTTON_ATTACKERS_TURN,
			BUTTON_BUY_PENCIL,
			BUTTON_CAPTURE_PENCILS,
			BUTTON_DEFENDERS_TURN,
			BUTTON_CREATE_TOWER,
			BUTTON_DELETE_TOWER,
			BUTTON_UPGRADE_TOWER_SPEED,
			BUTTON_UPGRADE_TOWER_RANGE,
			BUTTON_UPGRADE_TOWER_DAMAGE,
			BUTTON_SHOW_CONTROLS_MENU,
			BUTTON_HIDE_CONTROLS_MENU,
			BUTTON_START_WAVE
		};
		
		/**
		 * @brief	Constructor
		 *
		 * @param	p_guienv A reference to the IGUIEnvironment given from the kernel.
		 */
		Gui(irr::gui::IGUIEnvironment* p_guienv);

		/**
		 * @brief	This function is used to draw the gui elements that were added to the m_guiEnvironment.
		 *
		 * @param	p_waveNumber The number of the current Wave.
		 * @param	p_waveSize The amount of Creatures to spawn by the current Wave.
		 * @param	p_creaturesSpawned The amount of Creatures spawned by the current wave.
		 * @param	p_fps The amount of Frames Per Seconds the Game Runs.
		 * @param	p_player1Points The points Player 1 has.
		 * @param	p_player2Points The points Player 2 has.
		 */
		void UpdateGui(int p_waveNumber, int p_waveSize, 
				int p_creaturesSpawned, int p_fps,
				int p_player1Points, int p_player2Points);

		/**
		 * @brief	Shows a menu with a button to close the Game.
		 *
		 *			The following buttons will be shown on the menu:
		 *			- return:	Hides the menu.
		 *			- stop:		Stops the Game.
		 * @author	Michel van Os.
		 */
		void ShowMenu();

		/**
		 * @brief	Hides the menu.
		 */
		void HideMenu();

		/**
		 * @brief	Show the Controls Menu.
		 */
		void ShowControlsMenu();

		/**
		 * @brief	Hides the Controls Menu.
		 */
		void HideControlsMenu();

		/**
		 * @brief	Show the victory image for the defending player.
		 *
		 *			If p_playerType is TYPE_DEFENDER then the Victory image will be shown.
		 *			If p_playerType is TYPE_ATTACKER then the Defeated image will be shown.
		 * @author	Michel van Os.
		 * @param	p_playerType The PlayerType that won.
		 */
		void ShowVictory(PlayerType p_playerType);

		/**
		 * @brief	Hides the victory image.
		 *
		 * @author	Michel van Os.
		 */
		void HideVictory();

		/**
		 * @brief	Changes the enabled state for the Attackers Turn Button.
		 *
		 * @author	Michel van Os.
		 * @param	p_state The new state for the Button.
		 */
		void SetButtonAttackersTurnEnabled(bool p_state);

		/**
		 * @brief	Changes the enabled state for the Attackers Actions Buttons.
		 *
		 *			The Attackers Actions buttons are:
		 *			- Buy Pencil
		 *			- Capture Pencils
		 * @author	Michel van Os.
		 * @param	p_state The new state for the Buttons.
		 */
		void SetButtonAttackersActionsEnabled(bool p_state);

		/**
		 * @brief	Changes the enabled state for the Defenders Turn Button.
		 *
		 * @author	Michel van Os.
		 * @param	p_state The new state for the Button.
		 */
		void SetButtonDefendersTurnEnabled(bool p_state);

		/**
		 * @brief	Changes the enabled state for the Defenders Actions Buttons.
		 *
		 *			The Defenders Actions buttons are:
		 *			- Create Tower
		 *			- Delete Tower
		 *			- Update Tower Speed
		 *			- Update Tower Range
		 *			- Update Tower Damage
		 * @author	Michel van Os.
		 * @param	p_state The new state for the Buttons.
		 */
		void SetButtonDefendersActionsEnabled(bool p_state);

		/**
		 * @brief	Changes the enabled state for the Start Wave Button.
		 *
		 * @author	Michel van Os.
		 * @param	p_state The new state for the Button.
		 */
		void SetButtonStartWaveEnabled(bool p_state);

	private:
		irr::gui::IGUIEnvironment* m_guiEnvironment;
		irr::gui::IGUIImage* m_menu;
		irr::gui::IGUIImage* m_menuControls;
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
		bool m_controlsMenuIsActive;
		bool m_victoryIsActive;
		bool m_defeatSceenIsActive;

		/**
		 * @Creates all the control objects for the GUI
		 */
		void CreateGUIControls();

		/** 
		 * @brief Converts a string and an int to a wString so it can be used easily with Irrlicht
		 * @return wString that can be used easily with Irrlicht
		 * @param The method gets an string and an int as input which get converted
		 */
		std::wstring StringToWString(std::string,int);
	};
}
#endif