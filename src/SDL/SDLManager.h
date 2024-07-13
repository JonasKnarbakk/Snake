/*
 * @file: SDLManager.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: Singleton class to be used for SDL initialization,
 *				 window management, and rendering (blit'ing).
 *				 NB: Ment for games, so it's containing a Master/Main
 *				 window.
 */

#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "SDLError.h"
#include "SDLWindow.h"

class SDLManager {
  public:
    /* Frees memory; closes windows quits SDL */
    ~SDLManager();

    /* Standard Meyer's singleton class to access the object. */
    static SDLManager &Instance() {
        static SDLManager sdl;
        return sdl;
    }

    /* Initializes SDL with the given flags */
    void init(Uint32 flags = SDL_INIT_VIDEO);

    /* Creates a SDL window, se SDL documentation for flag options. */
    int createWindow(const std::string &title,
                     const int &width = 640,
                     const int &height = 480,
                     const int &x = SDL_WINDOWPOS_CENTERED,
                     const int &y = SDL_WINDOWPOS_CENTERED,
                     const Uint32 &flags = SDL_WINDOW_SHOWN,
                     const bool &mainWindow = false);

    /* Returns the renderer to the specified window */
    SDL_Renderer *const getRenderer(const unsigned int &windowIndex = NULL) const;

    /* Returns the index of the main/master window */
    const unsigned int *const getMainWindow() const;

    /* Sets the main/master window */
    void setMainWindow(const unsigned int &windowIndex);

    /* Closes the given window (index) */
    void closeWindow(const unsigned int &windowIndex);

    /* Renders/blits the given window (index) */
    void renderWindow(const unsigned int &windowIndex);

    /* Returns the width of the window as a value divisible by 64 */
    int getWindowWidth();

    /* Returns the height of the window as a value divisible by 64 */
    int getWindowHeight();

    /* Returns the window as and SDL_Window pointer */
    SDL_Window *getWindow();

    /* Renders/blits all open windows */
    void render();

  private:
    SDLManager();                              // hidden constructor (singleton)
    SDLManager(const SDLManager &);            // hidden copy constructor
    SDLManager &operator=(const SDLManager &); // hidden assignment op.

    std::vector<std::unique_ptr<SDLWindow>> m_windows; // list of windows
    unsigned int m_mainWindow;                         // index of main/master window
    SDL_Window *m_window;
};

#endif