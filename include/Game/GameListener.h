#ifndef __GAME__GAMELISTENER__H__
#define __GAME__GAMELISTENER__H__

namespace Game
{
	/**
	 * @brief	The GameListener handles the events triggered by the Playground.
	 *			
	 * @author	Michel van Os.
	 */
	class GameListener
	{
	public:
		/**
		 * @brief	Triggered when a Creature is spawned.
		 *
		 * @author	Michel van Os.
		 */
		virtual void OnCreatureSpawned() = 0;
		
		/**
		 * @brief	Triggered when a Creature reached the Castle.
		 *
		 * @author	Michel van Os.
		 */
		virtual void OnCreatureReachedCastle() = 0;
		
		/**
		 * @brief	Triggered when a Creature is killed.
		 *
		 * @author	Michel van Os.
		 */
		virtual void OnCreatureKilled() = 0;
		
		/**
		 * @brief	Triggered when a Wave is ended.
		 *
		 * @author	Michel van Os.
		 */
		virtual void OnWaveEnded() = 0;
	};
}

#endif