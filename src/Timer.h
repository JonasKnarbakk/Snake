/*
 * @file: Timer.h
 * @version: 1.0.0 <11.02.2013>
 * @author: Stig M. Halvorsen <halsti@nith.no>
 *
 * @description: A singleton cross-platform C++11 clock
 *				 based class for timing. Gives access to
 *				 passed time since last frame (deltatime)
 *				 and total runtime (since init).
 */

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

// Typedefs to make "life" easier
typedef std::chrono::milliseconds milliseconds;
typedef std::chrono::high_resolution_clock hr_clock;
typedef hr_clock::time_point time_point;
typedef hr_clock::duration duration;

class Timer
{
public:
	/* Standard Meyer's singleton instance to access object */
	static Timer& Instance() {
		static Timer t;
		return t;
	}

	/* This function doesn't do anything, but invokes the constructor (initializing)! */
	inline void init() {};

	/* Updates the timer, re-calculates delta time. */
	void update();

	/* Returns current delta time in seconds. */
	const float& deltaTime() const;

	/* Returns total runtime in seconds, since init() */
	float elapsedTime() const;
private:
	Timer(); // Hidden constructor, initializing stuff
	Timer(const Timer&); // Hidden copy constructor
	Timer& operator=(const Timer&); // Hidden assigment op.

	const time_point m_startTick; // time point at init
	time_point m_currentTick; // current time_point
	time_point m_lastTick; // last frame's time_pooint
	float m_deltaTime; // time since last frame
};

#endif