/*
 * @file: SDLManager.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: Singleton class to be used for SDL initialization,
 *				 window management, and rendering (blit'ing).
 *				 NB: Ment for games, so it's containing a Master/Main
 *				 window.
 */

#include <sstream>
#include <cmath>
#include "SDLManager.h"

SDLManager::SDLManager() {
    m_mainWindow = NULL;
}

/* Initializes SDL with the given flags */
void SDLManager::init(Uint32 flags) {
    if (SDL_Init(flags) < 0) {
        std::stringstream msg;
        msg << "Could not initialize SDL: " << SDL_GetError();

        throw SDLError(msg.str());
    }
}

/* Quits SDL, windows close when they go out of scope */
SDLManager::~SDLManager() {
    SDL_Quit();
}

/* Creates a SDL window, se SDL documentation for flag options. */
int SDLManager::createWindow(const std::string &title,
                             const int &width,
                             const int &height,
                             const int &x,
                             const int &y,
                             const Uint32 &flags,
                             const bool &mainWindow) {
    // Create the window where we will draw.
    m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);

    // Check for errors
    if (m_window == NULL) {
        std::stringstream msg;
        msg << "Could not create window; \"" << title << "\", details: " << SDL_GetError();

        throw SDLError(msg.str());
    }

    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    SDL_Renderer *renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) // Check for render errors
    {
        std::stringstream msg;
        SDL_DestroyWindow(m_window); // clean up

        msg << "Could not create window renderer; \"" << title << "\", details: " << SDL_GetError();

        throw SDLError(msg.str());
    }

    // Select the color for drawing. It is set to black here.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);

    // Retrieve the index of the new window by getting current size
    int index = m_windows.size();

    // Create and add the new window
    m_windows.push_back(std::unique_ptr<SDLWindow>(new SDLWindow(m_window, renderer, true)));

    // Set main window if not already set or asked to
    if (mainWindow || (m_mainWindow == NULL)) {
        m_mainWindow = index;
    }

    renderWindow(index); // Render window immediately
    return index;
}

/* Sets the main/master window */
void SDLManager::setMainWindow(const unsigned int &windowIndex) {
    if ((m_windows.size() > windowIndex) && m_windows[windowIndex]->m_open) {
        m_mainWindow = windowIndex;
    }
}

/* Returns the renderer to the specified window */
SDL_Renderer *const SDLManager::getRenderer(const unsigned int &windowIndex) const {
    if (m_windows.size() > windowIndex) {
        return m_windows[windowIndex]->m_renderer;
    }

    return NULL;
}

/* Returns the index of the main/master window */
const unsigned int *const SDLManager::getMainWindow() const {
    return &m_mainWindow;
}

/* Closes the given window (index) */
void SDLManager::closeWindow(const unsigned int &windowIndex) {
    if (m_windows.size() > windowIndex) {
        m_windows[windowIndex]->m_open = false;
        SDL_DestroyRenderer(m_windows[windowIndex]->m_renderer);
        SDL_DestroyWindow(m_windows[windowIndex]->m_window);
    }
}

/* Renders/blits the given window (index) */
void SDLManager::renderWindow(const unsigned int &windowIndex) {
    if ((m_windows.size() > windowIndex) && m_windows[windowIndex]->m_open) {
        SDL_RenderPresent(m_windows[windowIndex]->m_renderer);
    }
}

/*------------------- Student added functions ---------------*/

int SDLManager::getWindowWidth() {
    int windowWidth = 0;
    int windowHeight = 0;

    SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

    // The game is based on 64x64 sprites so when we report
    // the screen width we want something divisible by 64
    windowWidth = round(windowWidth / 64) * 64;
    return windowWidth;
}

int SDLManager::getWindowHeight() {
    int windowWidth = 0;
    int windowHeight = 0;

    SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);

    // The game is based on 64x64 sprites so when we report
    // the screen height we want something divisible by 64
    windowHeight = round(windowHeight / 64) * 64;
    return windowHeight;
}

/*------------------- END Student added functions ---------------*/

SDL_Window *SDLManager::getWindow() {
    return m_window;
}

/* Renders/blits all open windows */
void SDLManager::render() {
    for (unsigned int i = 0; i < m_windows.size(); ++i) {
        renderWindow(i);
    }
}