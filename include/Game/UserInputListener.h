#ifndef __GAME__USERINPUTLISTENER__H__
#define __GAME__USERINPUTLISTENER__H__

#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	The UserInputListener handles the events triggered by the EventHandler.
	 * 
	 * @author	Michel van Os.
	 */
	class UserInputListener
	{
	public:
		/**
		 * @brief	Triggered when the Stop Game button is clicked.
		 *
		 * @author	Michel van Os.
		 */
		virtual void OnStopGame() = 0;

		/**
		 * @brief	Triggered when the Start Wave button is clicked.
		 *
		 * @author	Michel van Os.
		 */
		virtual	void OnStartWave() = 0;

		/**
		 * @brief	Triggered when the Attackers Turn button is clicked.
		 *
		 * @author	Michel van Os.
		 */
		virtual void OnPlacePencils() = 0;

		/**
		 * @brief	Triggered when the Buy Pencil button is clicked.
		 *
		 * @author	Michel van Os.
		 */
		virtual void OnBuyPencil() = 0;

		/**
		 * @brief	Triggered when the Defenders Turn button is clicked.
		 *
		 * @author	Michel van Os.
		 */
		virtual void OnPlaceTowers() = 0;
		
		/**
		 * @brief	Triggered when the Create Tower button is clicked
		 *			followed by a mouse click on the playground.
		 *
		 * @author	Michel van Os.
		 * @param	p_position The screen coordinates where the mouse is clicked.
		 */
		virtual void OnTowerCreate(irr::core::vector2di p_position) = 0;
		
		/**
		 * @brief	Triggered when the Destroy Tower button is clicked
		 *			followed by a mouse click on the playground.
		 *
		 * @author	Michel van Os.
		 * @param	p_position The screen coordinates where the mouse is clicked.
		 */
		virtual void OnTowerDestroy(irr::core::vector2di p_position) = 0;
		
		/**
		 * @brief	Triggered when the Upgrade Tower Speed button is clicked
		 *			followed by a mouse click on the playground.
		 *
		 * @author	Michel van Os.
		 * @param	p_position The screen coordinates where the mouse is clicked.
		 */
		virtual void OnTowerUpgradeSpeed(irr::core::vector2di p_position) = 0;
		
		/**
		 * @brief	Triggered when the Upgrade Tower Range button is clicked
		 *			followed by a mouse click on the playground.
		 *
		 * @author	Michel van Os.
		 * @param	p_position The screen coordinates where the mouse is clicked.
		 */
		virtual void OnTowerUpgradeRange(irr::core::vector2di p_position) = 0;
		
		/**
		 * @brief	Triggered when the UPgrade Tower Damage button is clicked
		 *			followed by a mouse click on the playground.
		 *
		 * @author	Michel van Os.
		 * @param	p_position The screen coordinates where the mouse is clicked.
		 */
		virtual void OnTowerUpgradeDamage(irr::core::vector2di p_position) = 0;
	};
}

#endif