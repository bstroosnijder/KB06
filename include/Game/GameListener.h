#ifndef __GAME__GAMELISTENER__H__
#define __GAME__GAMELISTENER__H__

namespace Game
{
	/**
	 * @brief	TODO
	 *			
	 * @author	Alex Hodes
	 */
	class GameListener
	{
	public:
		virtual void OnCreatureSpawned() = 0;
		virtual void OnCreatureReachedCastle() = 0;
		virtual void OnCreatureKilled() = 0;
		virtual void OnCreatureHit() = 0;
		virtual void OnProjectileMissed() = 0;
		virtual void OnProjectileFired() = 0;
		virtual void OnWaveEnded() = 0;
	};
}

#endif