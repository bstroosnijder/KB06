#ifndef __GUI__H__
#define __GUI__H__

#include <irrlicht.h>
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
		 */
		void drawGui();

		/**
		 *@brief This function is used to exit the program
		 */
		bool exitButtonPressed();

		irr::gui::IGUIEnvironment* returnGuiEnv();




	private:
		irr::gui::IGUIEnvironment* m_guienv;
		irr::gui::IGUIButton* exitButton;
		irr::gui::IGUIButton* menuButton;
	};
}
#endif