#ifndef __GAME__TIMER__H__
#define __GAME__TIMER__H__

#include <iostream>
#include <conio.h>
#include <time.h>

namespace Game
{
	/**
	 * @brief	This class acts as a timer to control events in the game.
	 * 
	 * @author	Bram van Elderen.
	 * @author	Michel van Os.
	 */
	class Timer
	{
	public:
		/**
		 * @brief	Creates the Timer.
		 */
		Timer();

		/**
		 * @brief	Starts the timer.
		 */
		void Start();

		/**
		 * @brief	Stops the timer.
		 */
		void Stop();

		/**
		 * @brief	Resets the timer.
		 */
		void Reset();

		/**
		 * @brief	Returns the state of the timer.
		 */
		bool IsRunning();

		/**
		 * @brief	Returns the current time of the Timer.
		 */
		unsigned long GetTime();

		/**
		 * @brief	Returns if the timer is passed the given parameter.
		 * @param	p_seconds The timer uses p_seconds to check if the counter passed
		 * that point or not
		 */
		bool IsOver(unsigned long p_seconds);

	private:
		bool m_resetted;
		bool m_running;
		unsigned long m_beginTime;
		unsigned long m_endTime;
	};
}

#endif