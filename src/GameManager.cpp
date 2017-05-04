/*
 * @file: GameManager.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A singleton class to control all gameplay.
 */

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "SDL/SDLBmp.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Timer.h"
#include "Handlers/MusicHandler.hpp"

/* Initializes SDL, creates the game window and fires off the timer. */
GameManager::GameManager()
{
	SDLManager::Instance().init();
	m_window = SDLManager::Instance().createWindow("My Awesome SDL 2.0 Game", 640, 640);
    Timer::Instance().init();
    TTF_Init();
    Sans = TTF_OpenFont("Assets/fonts/FreeSans.ttf", 114); //this opens a font style and sets a size
    if(Sans == NULL){
        SDL_Log("While trying to load font: %s", TTF_GetError());
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    } else {
        eat = Mix_LoadWAV( "Assets/sfx/oluu.wav" );
        death = Mix_LoadWAV( "Assets/sfx/death.wav" );
    }
    if(eat == NULL){
        SDL_Log("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}


/* Kicks off/is the the gameloop */
void GameManager::play()
{
	bool notGameOver = true;
	bool playParticle = false;

	int particleStage = 1;

	enum Directions {
	    DIR_UP,
	    DIR_DOWN,
	    DIR_FORWARD,
	    DIR_BACKWARD
	};

	int dir = DIR_FORWARD;

	// Load bitmaps
	SDLBmp backround("Assets/gfx/sdl2.bmp");
	SDLBmp playerUp("Assets/gfx/SnakeHeadUp.bmp");
	SDLBmp playerRight("Assets/gfx/SnakeHeadRight.bmp");
	SDLBmp playerDown("Assets/gfx/SnakeHeadDown.bmp");
	SDLBmp playerLeft("Assets/gfx/SnakeHeadLeft.bmp");
	SDLBmp body("Assets/gfx/SnakeHead.bmp");
	SDLBmp grass("Assets/gfx/Grass.bmp");
	SDLBmp apple("Assets/gfx/Apple.bmp");
	SDLBmp scissor("Assets/gfx/Scissor.bmp");
	SDLBmp particle1("Assets/gfx/Particle1.bmp");
	SDLBmp particle2("Assets/gfx/Particle2.bmp");
	SDLBmp particle3("Assets/gfx/Particle3.bmp");
	SDLBmp particle = particle1;
    // Give the apple a random start position
    apple.x = (rand() % 20) * 32;
    apple.y = (rand() % 20) * 32;

    scissor.x = (rand() % 20) * 32;
    scissor.y = (rand() % 20) * 32;

    // Struct to store information about the player.
    struct playerCharacter{
        int x;
        int y;
    };

    playerCharacter player;
    
    // Set the player starting position
    player.x = 0;
    player.y = 0;

	// Calculate render frames per second (second / frames) (60)
	float render_fps = 1.f / 60.f;
	m_lastRender = render_fps; // set it to render immediately

	float step_time = 0.1f;
	float step_counter = 0.0f;
	unsigned int score = 0;

	struct bodyPos{
	    int x;
	    int y;
	};

	bodyPos parts[20*20];

	// Load some music
	MusicHandler musicHandler;

	musicHandler.loadMusicTrack("Assets/music/soundtrack.mp3");
	musicHandler.start();

	// Gameloop
	while (notGameOver)
	{
		// Update input and deltatime
		InputManager::Instance().Update();
		Timer::Instance().update();

		// Calculate displacement based on deltatime
		float displacement = 32.0f;

		/* Input Management */

		// Left key
		if (InputManager::Instance().KeyDown(SDL_SCANCODE_LEFT) ||
			InputManager::Instance().KeyStillDown(SDL_SCANCODE_LEFT))
		{
			dir = DIR_BACKWARD;
		}
		
		// Right key
		if (InputManager::Instance().KeyDown(SDL_SCANCODE_RIGHT) ||
			InputManager::Instance().KeyStillDown(SDL_SCANCODE_RIGHT))
		{
		    dir = DIR_FORWARD;
		}

		// Key up
		if (InputManager::Instance().KeyDown(SDL_SCANCODE_UP) ||
			InputManager::Instance().KeyStillDown(SDL_SCANCODE_UP))
		{
		    dir = DIR_UP;
		}

		// Key down
		if (InputManager::Instance().KeyDown(SDL_SCANCODE_DOWN) ||
			InputManager::Instance().KeyStillDown(SDL_SCANCODE_DOWN))
		{
		    dir = DIR_DOWN;
		}

		// Exit on [Esc], or window close (user X-ed out the window)
		if (InputManager::Instance().hasExit() || InputManager::Instance().KeyDown(SDL_SCANCODE_ESCAPE))
		{
			notGameOver = false;
		}

		// Update time since last render
		m_lastRender += Timer::Instance().deltaTime();
        step_counter += Timer::Instance().deltaTime();

        // Check if its time to move
        if(step_counter >= step_time){

            // Position the tail elements before the head updates its position
            for(int i = (int)score; i >= 0; i--){
                if(i > 0){
                    parts[i].x = parts[i-1].x;
                    parts[i].y = parts[i-1].y;
                } else {
                    parts[i].x = player.x;
                    parts[i].y = player.y;
                }
            }

            // Update the head position according to the direction we are facing
            switch(dir){
                case DIR_UP:
                    player.y -= displacement;
                    break;
                case DIR_DOWN:
                    player.y += displacement;
                    break;
                case DIR_FORWARD:
                    player.x += displacement;
                    break;
                case DIR_BACKWARD:
                    player.x -= displacement;
                    break;
            }
           
            // Check for game over states
            if(player.x >= 640 || player.x < 0 || player.y >= 640 || player.y < 0){
                notGameOver = false;
                SDL_Log("You died.");
                Mix_PlayChannel( -1, death, 0 );
                SDL_Delay(1000);
            }

            for(int i = 0; i <= (int)score; i++){
                if(player.x == parts[i].x && player.y == parts[i].y){
                    notGameOver = false;
                    SDL_Log("You died.");
                    Mix_PlayChannel( -1, death, 0 );
                    SDL_Delay(1000);
                }
            }            // Reset the step counter
            step_counter = 0.0f;
            if(playParticle){
                switch(particleStage){
                    case 1:
                        particleStage = 2;
                        break;
                    case 2:
                        particleStage = 3;
                        break;
                    case 3:
                        particleStage = 4;
                        break;
                    default:
			            particleStage = 1;
                        playParticle = false;
                        break;
                }
            }
            // If we hit an apple, respawn it at a different location and increment the score
            if(player.x == apple.x && player.y == apple.y){
                apple.x = (rand() % 20) * 32;
                apple.y = (rand() % 20) * 32;
                score++;
                Mix_PlayChannel( -1, eat, 0 );
                particle1.x = player.x;
                particle1.y = player.y;
                particle2.x = player.x;
                particle2.y = player.y;
                particle3.x = player.x;
                particle3.y = player.y;
                playParticle = true;
                // SDL_Log("Player score is: %i", score);
            }
            if(player.x == scissor.x && player.y == scissor.y){
                scissor.x = (rand() % 20) * 32;
                scissor.y = (rand() % 20) * 32;
                if(score > 0){
                    score--;
                }
                Mix_PlayChannel( -1, death, 0 );
                if(score <= 0){
                    notGameOver = false;
                    SDL_Delay(1000);
                }
            }


		}

		// Check if it's time to render
		if (m_lastRender >= render_fps)
		{
			// Draw the background, we are using a 32x32 image
			// so it can scale if we want to change the window size
			grass.x = 0;
			grass.y = 0;
			for(int y = 0; y < 20; y++){
			    for(int x = 0; x < 20; x++){
			        grass.draw();
			        grass.x += 32;
			    }
                grass.y += 32;
                grass.x = 0;
			}
			
			// Draw each body part relative to the accumulated score
			for(int i = 0; i < (int)score; i++){
			    body.x = parts[i].x;
			    body.y = parts[i].y;
			    body.draw();
			}
			// Draw the head according to the direction we are facing
			switch(dir){
		        case DIR_FORWARD:
		            playerRight.x = player.x;
		            playerRight.y = player.y;
		            playerRight.draw();
			        break;
			    case DIR_DOWN:
			        playerDown.x = player.x;
			        playerDown.y = player.y;
			        playerDown.draw();
                    break;
                case DIR_BACKWARD:
                    playerLeft.x = player.x;
                    playerLeft.y = player.y;
                    playerLeft.draw();
                    break;
			    default:
			        playerUp.x = player.x;
			        playerUp.y = player.y;
			        playerUp.draw();
			        break;
			}
			apple.draw();
			scissor.draw();
			if(playParticle){
			    switch(particleStage){
			        case 1:
			            particle1.draw();
			            break;
			        case 2:
			            particle2.draw();
			            break;
			        case 3:
			            particle3.draw();
			            break;
			    }
			}

			// Render the score text too the screen
            std::string scoreText = "Score: " + std::to_string(score);
			renderText(scoreText, (640/2)-75, 0);

			// Render window
			SDLManager::Instance().renderWindow(m_window);
			m_lastRender = 0.f;
		}

		// Sleep to prevent CPU exthaustion (1ms == 1000 frames per second)
		SDL_Delay(1);
	}
	TTF_Quit();
	Mix_FreeChunk(eat);
	Mix_FreeChunk(death);
}

void GameManager::renderText(std::string text, int x, int y){
    if(Sans != NULL){
        SDL_Color White = {255, 255, 255, 1};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
        SDL_Color Black = {0, 0, 0, 1};

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
        SDL_Surface* surfaceOutline = TTF_RenderText_Solid(Sans, text.c_str(), Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        SDL_Renderer *renderer = SDLManager::Instance().getRenderer(*(SDLManager::Instance().getMainWindow()));

        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
        SDL_Texture* Outline = SDL_CreateTextureFromSurface(renderer, surfaceOutline); //now you can convert it into a texture

        SDL_FreeSurface(surfaceMessage);
        SDL_FreeSurface(surfaceOutline);

        SDL_Rect Message_rect; //create a rect
        Message_rect.x = x;  //controls the rect's x coordinate 
        Message_rect.y = y; // controls the rect's y coordinte
        Message_rect.w = 150; // controls the width of the rect
        Message_rect.h = 50; // controls the height of the rect

        SDL_Rect Outline_rect; //create a rect
        Outline_rect.x = x+3;  //controls the rect's x coordinate 
        Outline_rect.y = y+3; // controls the rect's y coordinte
        Outline_rect.w = 150; // controls the width of the rect
        Outline_rect.h = 50; // controls the height of the rect

        //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance
        //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
        SDL_RenderCopy(renderer, Outline, NULL, &Outline_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

        SDL_DestroyTexture(Message);
        Message = NULL;
        SDL_DestroyTexture(Outline);
        Outline = NULL;
    }
}
