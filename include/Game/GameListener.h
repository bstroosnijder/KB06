#ifndef __GAME__GAMELISTENER__H__
#define __GAME__GAMELISTENER__H__

namespace Game
{
	class GameListener
	{
		virtual void CreatureSpawned() = 0;
		virtual void CreatureReachedCastle() = 0;
		virtual void CreatureKilled() = 0;
		virtual void CreatureHit() = 0;
		virtual void ProjectileMissed() = 0;
		virtual void ProjectileFired() = 0;
		virtual void WaveEnded() = 0;
	};
}

#endif