#ifndef __GAME__GAMESTATUS__H__
#define __GAME__GAMESTATUS__H__

namespace Game
{
	/**
	 * @brief	Used by the GameManager to store the current status of the Game.
	 *
	 * @author	Michel van Os.
	 */
	enum GameStatus
	{
		/// The game is started.
		GAME_STARTED,

		/// Attacker is placing pencils on the table
		ATTACKER_PLACE_PENCILS,

		/// Defender is placing, updating and deleting towers in the playground
		DEFENDER_PLACE_TOWERS,

		/// The current Wave of the Playground is spawning creatures at the Stargate.
		/// Creatures are walking towards the Castle.
		/// Towers are shooting Projectiles towards the Creatures.
		WAVE_RUNNING,

		/// All Game-entities stop.
		WAVE_PAUZED,

		/// All Creatures that should be spawned by the current Wave
		/// are killed or reached the Castle.
		WAVE_FINISHED,

		/// The attacker (PlayerType::TYPE_ATTACKER) has won the game.
		ATTACKER_VICTORY,

		/// The defender (PlayerType::TYPE_DEFENDER) has won the game.
		DEFENDER_VICTORY
	};
}

#endif