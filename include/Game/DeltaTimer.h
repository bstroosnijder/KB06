#ifndef __GAME__DELTATIMER__H__
#define __GAME__DELTATIMER__H__

#include <irrlicht.h>

namespace Game
{
	/**
	 * @brief	Used to keep the delta time for the game in milliseconds.
	 *
	 * @author	Michel van Os.
	 */
	class DeltaTimer
	{
	public:
		/**
		 * @brief	Creates the DeltaTimer
		 * @param	p_device A irr::ITimer used to retreive
		 *			the current time in milliseconds.
		 * @author	Michel van Os.
		 */
		DeltaTimer(irr::ITimer* p_timer);

		/**
		 * @brief	Destroys the DeltaTimer
		 *			
		 * @author	Michel van Os.
		 */
		~DeltaTimer();

		/**
		 * @brief	Returns the current delta time in milliseconds.
		 *			
		 * @author	Michel van os
		 */
		float GetDelta();

	private:
		irr::ITimer* m_timer;
		int m_time;
	};
};

#endif