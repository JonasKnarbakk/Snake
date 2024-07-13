/*
 * @file: Main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A SDL2.0 project to test if SDL2 is
 *				 instantiated properly, and is stable.
 *				 Includes a well working SDL2 input manager.
 *				 This project may be used as a start-off
 *				 point for SDL2 projects.
 *
 *				 NB: requires SDL 2.0.0-6799 (32 bit)
 */

#include <iostream>
#include "GameManager.h"

int main(int argc, char *argv[]) {
    // Try to fire off the "game", catch potential failures.
    try {
        // Moved here cause it caused problem with loading BMPs before window was initialised
        SDLManager::Instance().init(SDL_INIT_AUDIO);
        SDLManager::Instance().createWindow("My Awesome SDL 2.0 Game", 1536, 832);
        GameManager::Instance().play();
        return EXIT_SUCCESS;
    } catch (const SDLError &err) {
        std::cerr << "An SDL error occured: " << err.what() << std::endl;
    } catch (const std::bad_alloc &err) {
        std::cerr << "Memory allocation failure: " << err.what() << std::endl;
        return false;
    } catch (const std::exception &err) {
        std::cerr << "An error occured: " << err.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occured ..." << std::endl;
    }

    return EXIT_FAILURE;
}