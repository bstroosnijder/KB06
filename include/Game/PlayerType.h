#ifndef __GAME__PLAYERTYPE__H__
#define __GAME__PLAYERTYPE__H__

namespace Game
{
	/**
	 * @brief	Each player of game has a PlayerType.
	 *			
	 * @author	Michel van Os.
	 */
	enum PlayerType
	{
		/// The player that can place pencils on the table.
		TYPE_ATTACKER,

		/// The player that can place, remove, and upgrade Towers.
		TYPE_DEFENDER
	};
}

#endif