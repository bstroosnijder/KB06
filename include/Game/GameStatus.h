#ifndef __GAME__GAMESTATUS__H__
#define __GAME__GAMESTATUS__H__

namespace Game
{
	enum GameStatus
	{
		/// The game started.
		GAME_STARTED,

		/// Attacker places the pencils on the table
		ATTACKER_PLACE_PENCILS,

		/// Defender places, updates, deletes towers in the playground
		DEFENDER_PLACE_TOWERS,

		/// The wave in spawning creatures at the Stargate.
		/// Creatures are allowed to walk towards the Castle.
		WAVE_RUNNING,

		/// All Game-entities stop.
		WAVE_PAUZED,

		/// All Creatures are spawned and are dead or reached the Castle.
		WAVE_FINISHED,

		/// The attack has won the game.
		ATTACKER_VICTORY,

		/// The defender has won the game.
		DEFENDER_VICTORY
	};
}

#endif