#include "Game/DeltaTimer.h"

using namespace Game;

DeltaTimer::DeltaTimer(irr::ITimer* p_timer)
{
	m_timer = p_timer;

	m_timer->grab();
	m_time = m_timer->getTime();
}

DeltaTimer::~DeltaTimer()
{
	m_timer->drop();
}

float DeltaTimer::GetDelta()
{
	int m_now = m_timer->getTime();
	float m_delta = (m_now - m_time) / 1000.0f;
	m_time = m_now;

	return m_delta;
}