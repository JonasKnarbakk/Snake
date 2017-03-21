/*
 * @file: SDLBmp.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A class that makes it easy to load,
 *				 display and work with images.
 */

#include <sstream>
#include "SDLBmp.h"
#include "SDLManager.h"

/* Loads the given file on construction */
SDLBmp::SDLBmp(const std::string& file)
{
	// Load image using a CPU surface
	m_texture = NULL;
	SDL_Surface* surface = SDL_LoadBMP(file.c_str());
	// Set blue to be the transparent color
	SDL_SetColorKey(surface, true, SDL_MapRGB(surface->format, 0, 0, 255));

	// Check for errors
	if (surface == NULL)
	{
		std::stringstream msg;
		msg << "Failed to load bitmap: " << file
			<< " | details: " << SDL_GetError(); 

		throw SDLError(msg.str());
	}

	// SDL2 requires a window's renderer in order to make a hardware (GPU) surface (texture).
	// I think it's a bit strange but has probably something to do with the OpenGL context
	// being used.

	// Fetch the renderer from the Main/master window
	m_renderer = SDLManager::Instance().getRenderer(*(SDLManager::Instance().getMainWindow()));

	// Convert CPU surface into GPU texture
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	// Create the rect object, using the data from the surface object
	m_rect.h = surface->h;
	m_rect.w = surface->w;
	m_rect.x = 0;
	m_rect.y = 0;
	x = y = 0.0F; // Resets our custom floating coordinates

	// Free unnecessary CPU data
	SDL_FreeSurface(surface);

	if (m_texture == NULL) // check for errors
	{
		throw SDLError();
	}
}

/* Free's the memory consumed by the image data */
SDLBmp::~SDLBmp()
{
	SDL_DestroyTexture(m_texture);
}

/* Adds the image to the master window */
void SDLBmp::draw()
{
	m_rect.x = static_cast<int>(x); // cast our floats to ints
	m_rect.y = static_cast<int>(y);

	// Add object to renderer/window
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rect);
}
