#include "Game/Timer.h"

namespace Game
{
	Timer::Timer()
	{
		m_resetted = true;
		m_running = false;
		m_beginTime = 0;
		m_endTime = 0;
	}
	
	void Timer::Start()
	{
		if (!m_running)
		{
			if (m_resetted)
			{
				m_beginTime = (unsigned long) clock();
			}
			else
			{
				m_beginTime -= m_endTime - (unsigned long) clock();
			}

			m_running = true;
			m_resetted = false;
		}
	}

	void Timer::Stop()
	{
		if (m_running)
		{
			m_endTime = (unsigned long) clock();
			m_running = false;
		}
	}

	void Timer::Reset()
	{
		bool wereRunning = m_running;
		
		if (wereRunning)
			Stop();
		m_resetted = true;
		m_beginTime = 0;
		m_endTime = 0;
		if (wereRunning)
			Start();
	}

	bool Timer::IsRunning() 
	{
		return m_running;
	}

	unsigned long Timer::GetTime()
	{
		if (m_running)
		{
			return ((unsigned long) clock() - m_beginTime) / CLOCKS_PER_SEC;
		}
		else
		{
			return m_endTime - m_beginTime;
		}
	}

	bool Timer::IsOver(unsigned long p_seconds)
	{
		return p_seconds >= GetTime();
	}
}