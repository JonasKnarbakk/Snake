/*
 * @file: InputManager.cpp
 * @version: 2.0.3 <12.03.2015>
 * @author: Tomas Sandnes <santom@nith.no> - 2009 & 2015
 * @author: Kjetil Raaen <raakje@nith.no> - 2011
 * @author: Stig M. Halvorsen <halsti@nith.no> - 2013
 *
 * @description: A singleton State Snapshot input manager
 *				 using SDL2 for interactive input.
 *				 This is platform independent!
 */

#include "InputManager.h"

/* Initializes the key system. */
InputManager::InputManager()
{
	m_keys = 0;
	m_oldKeys = 0;
	m_keyCount = 0;
	m_mouseButtons = 0;
	m_oldMouseButtons = 0;
	m_mouseX = 0;
	m_mouseY = 0;

	// Creating an array for the current state is taken care of by SDL, so we just get ourselves a 
	// pointer to it. (Array will be deleted by SDL on app exit, so we can forget all about it.)
	m_keys = SDL_GetKeyboardState(&m_keyCount);

	// Allocate sufficent memory for the old keys array
	m_oldKeys = std::unique_ptr<Uint8>(new Uint8[m_keyCount]);

	// Copy over the key states
	memcpy(m_oldKeys.get(), m_keys, m_keyCount * sizeof(Uint8));

	// Pumping twice, to flush any pending keypresses.
	SDL_PumpEvents();
	SDL_PumpEvents();
}

/* Updates the key states */
void InputManager::Update()
{
	// Setting "old" states equal to those aquired on last Update().
	m_oldMouseButtons = m_mouseButtons;
	memcpy(m_oldKeys.get(), m_keys, m_keyCount * sizeof(Uint8));

	// SDL_PollEvent() performs a SDL_PumpEvent():
	// Pumping events, meaning we update SDL's input states to match current inputs.
	// Key changes gets updated automatically, as we hold a pointer to SDL's internal key array.
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		// Check if user X-ed out a window
		if (event.type == SDL_QUIT)
		{
			m_exit = true;
		}
	}

	// We have to fetch Mouse Events manually
	m_mouseButtons = SDL_GetRelativeMouseState(&m_mouseX, &m_mouseY);
}
