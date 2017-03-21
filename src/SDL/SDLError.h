/*
 * @file: SDLError.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A custom exception specializing in SDL errors.
 */

#ifndef SDL_ERROR_H
#define SDL_ERROR_H

#include <exception>
#include <string>

class SDLError : public std::exception
{
public:
	/* Creates an exception with the default SDL_GetError() as message */
	SDLError();

	/* Creates an exception with the givens string as message */
	SDLError(const std::string&);

	/* Virtual destructor due to inheritance */
	virtual ~SDLError() throw();

	/* Overloaded inherited method. Returns the error message */
	virtual const char* what() const throw();
private:
	std::string m_message; // Contains error message
};

#endif