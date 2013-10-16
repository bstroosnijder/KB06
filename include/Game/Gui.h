#ifndef __GUI__H__
#define __GUI__H__

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
		enum
		{
			QUIT_BUTTON = 101,
			MENU_BUTTON = 102,
			ClEAR_BUTTON = 103,
			TOWER_BUTTON = 104,
			SELL_BUTTON = 105,
			CONTROLS_BUTTON = 107,
			STARTGAME_BUTTON = 108
		};
	
	public:
		
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
		void UpdateGui(int p_waveNumber,int p_amountOfCreatures,int p_fps, int p_playerHealth, int p_resources);

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


	private:
		irr::gui::IGUIEnvironment* m_guienv;
		irr::gui::IGUIImage* m_menu;
		irr::gui::IGUIImage* m_controls;
		irr::gui::IGUIStaticText* m_amountOfCreatures;
		irr::gui::IGUIStaticText* m_waveNumber;
		irr::gui::IGUIStaticText* m_fps;
		irr::gui::IGUIStaticText* m_playerHealth;
		irr::gui::IGUIStaticText* m_playerResources;
		int m_screenWidth;
		int m_screenHeight;
		bool m_menuIsActive;
		bool m_controlsMenuIsActive;
		bool m_victoryIsActive;
		bool m_defeatSceenIsActive;

		/** 
		 * @brief Converts a string and an int to a wString so it can be used easily with Irrlicht
		 * @param The method gets an string and an int as input which get converted
		 */
		std::wstring stringToWString(std::string,int);
	};
}
#endif