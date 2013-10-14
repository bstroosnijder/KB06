#ifndef __GAME__TIMER__H__
#define __GAME__TIMER__H__

#include <iostream>
#include <conio.h>
#include <time.h>

namespace Game
{
	/**
	 * @brief This class acts as a timer to control events in our game
	 * 
	 * @author Bram van Elderen
	 */
	class Timer
	{
	public:
		/**
		 * @brief Constructor
		 */
		Timer();

		/**
		 * @brief Start the timer
		 */
		void Start();

		/**
		 * @brief Stop the timer
		 */
		void Stop();

		/**
		 * @brief Reset the timer
		 */
		void Reset();

		/**
		 * @brief Returns the state of the timer
		 */
		bool IsRunning();

		/**
		 * @brief Returns the current time of the Timer
		 */
		unsigned long GetTime();

		/**
		 * @brief Returns if the timer is passed the given parameter
		 * @param The timer uses p_seconds to check if the counter passed
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