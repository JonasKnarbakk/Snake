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

#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "GameManager.h"

int main()
{
	// Try to fire off the "game", catch potential failures.
	try
	{
		GameManager::Instance().play();
		return EXIT_SUCCESS;
	}
	catch(const SDLError& err)
	{
		std::cerr << "An SDL error occured: "
				  << err.what() << std::endl;
	}
	catch(const std::bad_alloc& err)
	{
		std::cerr << "Memory allocation failure: "
				<< err.what() << std::endl;
		return false;
	}
	catch(const std::exception& err)
	{
		std::cerr << "An error occured: "
				  << err.what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "An unknown error occured ..." << std::endl;
	}

	return EXIT_FAILURE;
}
