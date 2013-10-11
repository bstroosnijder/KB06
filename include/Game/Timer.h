#ifndef __GAME__TIMER__H__
#define __GAME__TIMER__H__

#include <iostream>
#include <conio.h>
#include <time.h>

namespace Game
{
	class Timer
	{
	public:
		Timer();

		void Start();
		void Stop();
		void Reset();
		bool IsRunning();
		unsigned long GetTime();
		bool IsOver(unsigned long seconds);

	private:
		bool m_resetted;
		bool m_running;
		unsigned long m_beginTime;
		unsigned long m_endTime;
	};
}

#endif