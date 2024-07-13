/*
 * @file: SDLWindow.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A wrapper for managing native SDL_Windows.
 *				 Each window needs a renderer, and a open/closed state.
 *				 This takes care of it all, including freeing memory!
 */

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL.h>

class SDLWindow {
  public:
    /* Empty inline constructor with empty data */
    SDLWindow() : m_window(NULL), m_renderer(NULL), m_open(false) {}

    /* Inline constructor, sets member data */
    SDLWindow(SDL_Window *window, SDL_Renderer *renderer, const bool &open = false)
        : m_window(window), m_renderer(renderer), m_open(open) {}

    /* Closes window and free's memory */
    ~SDLWindow() {
        if (m_open) {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            m_open = false;
        }
    }

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    bool m_open;
};

#endif