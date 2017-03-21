/*
 * @file: SDLMath.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A currently unused math library which is 
 *				 supposed to be used for missing math functions
 *				 and graphical math functions.
 *
 *				 NB: Should be template based as far as possible.
 */

#ifndef SDL_MATH_H
#define SDL_MATH_H

#include <cmath>

// Put it in its own namespace to prevent name conflicts.
namespace sdl
{
	/* Finds the closest whole number of the given number. It is supposed
	   to be in STL as of C++11, but VS12 has ignored it for some reason. */
	template <class T>
	T round(T number)
	{
		return std::floor(number + static_cast<T>(0.5F));
	}
}

#endif