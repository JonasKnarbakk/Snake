/*
 * @file: SDLError.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A custom exception specializing in SDL errors.
 */

#include <SDL.h>
#include "SDLError.h"

/* Creates an exception with the default SDL_GetError() as message */
SDLError::SDLError() : exception() {
    m_message = SDL_GetError();
}

/* Creates an exception with the givens string as message */
SDLError::SDLError(const std::string &msg) : exception() {
    m_message = msg;
}

SDLError::~SDLError() throw() {}

/* Overloaded inherited method. Returns the error message */
const char *SDLError::what() const throw() {
    return m_message.c_str();
}