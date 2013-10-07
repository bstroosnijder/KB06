#ifndef __GAME__DELTATIMER__H__
#define __GAME__DELTATIMER__H__

#include <irrlicht.h>

namespace Game
{
	class DeltaTimer
	{
	public:
		DeltaTimer(irr::ITimer* p_device);
		~DeltaTimer();

		float GetDelta();

	private:
		irr::ITimer* m_timer;
		int m_time;
	};
};

#endif