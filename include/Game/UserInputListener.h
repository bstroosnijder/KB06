#ifndef __GAME__USERINPUTLISTENER__H__
#define __GAME__USERINPUTLISTENER__H__

#include <irrlicht.h>

namespace Game
{
	/**
	 * @author	Michel van Os.
	 */
	class UserInputListener
	{
	public:
		virtual void OnStopGame() = 0;

		virtual	void OnStartWave() = 0;
		virtual void OnPlacePencils() = 0;
		virtual void OnBuyPencil() = 0;
		virtual void OnPlaceTowers() = 0;

		virtual void OnTowerCreate(irr::core::vector2di p_position) = 0;
		virtual void OnTowerDestroy(irr::core::vector2di p_position) = 0;
		virtual void OnTowerUpgradeSpeed(irr::core::vector2di p_position) = 0;
		virtual void OnTowerUpgradeRange(irr::core::vector2di p_position) = 0;
		virtual void OnTowerUpgradeDamage(irr::core::vector2di p_position) = 0;
	};
}

#endif