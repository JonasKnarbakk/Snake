/*
 * @file: Timer.cpp
 * @version: 1.0.0 <11.02.2013>
 * @author: Stig M. Halvorsen <halsti@nith.no>
 *
 * @description: A singleton cross-platform C++11 clock
 *				 based class for timing. Gives access to
 *				 passed time since last frame (deltatime)
 *				 and total runtime (since init).
 */


#include "Timer.h"

/* Initializes the timer, should be invoked through the init() function. */
Timer::Timer() : m_startTick(hr_clock::now())
{
	m_currentTick = m_startTick;
	m_lastTick = m_startTick;
	m_deltaTime = 0.0F;
}

// Updates the timer
void Timer::update()
{
	m_lastTick = m_currentTick;
	m_currentTick = hr_clock::now();

	// Delta time is calculated here as getDeltaTime() will be called often and should
	// thus not be calculated every time.
	milliseconds delta_ms = std::chrono::duration_cast<milliseconds>(m_currentTick - m_lastTick);
	m_deltaTime = static_cast<float>(delta_ms.count() / 1000.L);
}

/* Returns current delta time in seconds */
const float& Timer::deltaTime() const
{
	return m_deltaTime;
}

/* Returns elapsed runtime in seconds since init() */
float Timer::elapsedTime() const
{
	milliseconds elapsed_ms = std::chrono::duration_cast<milliseconds>(m_currentTick - m_startTick);
	return (static_cast<float>(elapsed_ms.count() / 1000.L));
}