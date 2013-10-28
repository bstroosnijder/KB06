#ifndef __GAME__USERINPUTLISTENER__H__
#define __GAME__USERINPUTLISTENER__H__

#include <irrlicht.h>

namespace Game
{
	class UserInputListener
	{
	public:
		virtual void OnStopGame() = 0;

		virtual	void OnStartWave() = 0;
		virtual void OnPlacePencils() = 0;
		virtual void OnPlaceTowers() = 0;

		virtual void OnTowerCreate() = 0;
		virtual void OnTowerDestroy() = 0;
		virtual void OnTowerUpgradeSpeed() = 0;
		virtual void OnTowerUpgradeRange() = 0;
		virtual void OnTowerUpgradeDamage() = 0;
	};
}

#endif