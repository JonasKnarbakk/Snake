/*
 * @file: SDLBmp.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A class that makes it easy to load,
 *				 display and work with images.
 */

#ifndef SDL_BMP_H
#define SDL_BMP_H

#include <string>
#include <SDL2/SDL.h>

class SDLBmp
{
public:
	/* Loads the given file on construction */
	SDLBmp(const std::string& file);
	
	/* Free's the memory consumed by the image data */
	~SDLBmp();

	/* Adds the image to the master window */
	void draw();

	/* "home brewed" float coordinates, SDL2 uses ints
		which is a bit too unpresice. */
	float x;
	float y;
private:
	SDL_Texture* m_texture; // Pixel data (on GPU)
	SDL_Renderer* m_renderer; // Pointer to window's renderer.
	SDL_Rect m_rect; // Used for w/h, placement and cropping.
};

#endif
