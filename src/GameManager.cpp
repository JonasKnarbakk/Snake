/*
 * @file: GameManager.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A singleton class to control all gameplay.
 */

#include "SDL/SDLBmp.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Timer.h"
#include "Apple.h"
#include <cmath>

/* Initializes SDL, creates the game window and fires off the timer. */
GameManager::GameManager()
    : player(0, 0, "Assets/gfx/snake-graphics.bmp"), background(0, 0, "Assets/gfx/GrassTile.bmp") {
    Timer::Instance().init();

    // Hide the mouse cursor
    SDL_ShowCursor(SDL_DISABLE);

    // Set the window to fullscreen
    // SDL_SetWindowFullscreen(SDLManager::Instance().getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Initialise variables
    gameOver = false;
    running = true;
    m_tickRate = 0.0f;
    m_spawnRate = 0.0f;
    srand(time(0));
    colorWhite = {255, 255, 255, 255};
    colorRed = {255, 0, 0, 255};

    // Load font
    textHandler.loadFont("Assets/fonts/FreeSans.ttf", 144);

    // Load music and sound effect
    music = soundHandler.loadMusic("Assets/sfx/musicSoundTrack.wav");
    gameOverSound = soundHandler.loadSFX("Assets/sfx/gameOver.wav");

    // Start the music track
    soundHandler.playMusic(music);

    // Spawn the first apple
    spawnApple();
}

/* Kicks off/is the the gameloop */
void GameManager::play() {
    // Calculate render frames per second (second / frames) (60)
    float render_fps = 1.f / 60.f;
    m_lastRender = render_fps; // set it to render immediately

    // Set update rate
    float tick_rate = 0.1f;

    // Gameloop
    while (running) {
        // Update input and deltatime
        InputManager::Instance().Update();
        Timer::Instance().update();

        // Handle input
        input();

        if (!gameOver) {
            // Update the tick timer
            m_tickRate += Timer::Instance().deltaTime();

            // We are emulating old snake so update and drawing only needs to happen once each tick
            if (m_tickRate >= tick_rate) {
                // Reset the counter
                m_tickRate = 0.0f;

                // Run the updates
                update();

                // Render to screen
                render();
            }

            // Sleep to prevent CPU exthaustion (1ms == 1000 frames per second)
            SDL_Delay(1);
        } else {
            if (!waitingForInput) {
                soundHandler.stopMusic(music);
                soundHandler.playSFX(gameOverSound);

                waitingForInput = true;
            }
        }
    }
    // Clean up all allocated memory
    spawner.cleanUp();
}

// Input Management
void GameManager::input() {
    // Left key
    if (InputManager::Instance().KeyDown(SDL_SCANCODE_LEFT)) {
        if (!gameOver) {
            if (player.canTurn(DIR_LEFT)) {
                player.setDirection(DIR_LEFT);
            }
        }
    }

    // Right key
    if (InputManager::Instance().KeyDown(SDL_SCANCODE_RIGHT)) {
        if (!gameOver) {
            if (player.canTurn(DIR_RIGHT)) {
                player.setDirection(DIR_RIGHT);
            }
        }
    }

    // Key up
    if (InputManager::Instance().KeyDown(SDL_SCANCODE_UP)) {
        if (!gameOver) {
            if (player.canTurn(DIR_UP)) {
                player.setDirection(DIR_UP);
            }
        }
    }

    // Key down
    if (InputManager::Instance().KeyDown(SDL_SCANCODE_DOWN)) {
        if (!gameOver) {
            if (player.canTurn(DIR_DOWN)) {
                player.setDirection(DIR_DOWN);
            }
        }
    }

    // Exit on [Esc], or window close (user X-ed out the window)
    if (InputManager::Instance().hasExit() || InputManager::Instance().KeyDown(SDL_SCANCODE_ESCAPE)) {
        running = false;
    }

    // R to reset the game when the game is over
    if (InputManager::Instance().KeyDown(SDL_SCANCODE_R)) {
        if (gameOver) {
            resetGame();
        }
    }
}

// Update Management
void GameManager::update() {

    // Check if the player hit a pick up object
    std::vector<GameObject *> activeObjects = spawner.getVector();
    std::vector<GameObject *>::iterator it;

    for (it = activeObjects.begin(); it != activeObjects.end(); ++it) {
        GameObject *object = *it;

        if (object != nullptr) {
            if (player.collides(object)) {
                player.increaseSize();
                spawner.despawn(object);
                spawnApple();
            }
        }
    }

    // Update all the objects in the spawner
    spawner.update();

    // Update the snake
    player.update();

    // Check if we died
    if (player.isDead()) {
        gameOver = true;
    }
}

// Rendering Management
void GameManager::render() {
    // Draw the background in 64x64 format so size of the window doesn't matter
    background.x = 0;
    background.y = 0;
    for (int y = 0; y < SDLManager::Instance().getWindowHeight(); y += 64) {
        for (int x = 0; x < SDLManager::Instance().getWindowWidth(); x += 64) {
            background.draw();
            background.x += 64;
        }
        background.y += 64;
        background.x = 0;
    }

    // Draw spawned objects
    spawner.draw();

    // Draw the player
    player.draw();

    // Draw score text to the screen
    std::string scoreText = "Score: " + std::to_string(player.getSize() - 1);
    textHandler.renderText(scoreText, SDLManager::Instance().getWindowWidth() / 2 - 100, 25, 200, 50, colorWhite);

    if (gameOver) {
        // Draw game over text to the screen
        textHandler.renderText("Game Over! press R to restart",
                               SDLManager::Instance().getWindowWidth() / 2 - 250,
                               SDLManager::Instance().getWindowHeight() / 2 - 37,
                               500,
                               75,
                               colorRed);
    }

    // Render to the window
    SDLManager::Instance().renderWindow(m_window);
}

// Will spawn an apple at a random location
void GameManager::spawnApple() {
    int spawnX = 0;
    int spawnY = 0;
    Apple tempApple(0, 0);

    // Try to spawn an apple that does not collide with the snake
    do {
        // Get a random width value
        spawnX = rand() % (SDLManager::Instance().getWindowWidth() - tempApple.width);
        // Get a random height value
        spawnY = rand() % (SDLManager::Instance().getWindowHeight() - tempApple.height);

        // Fit the random number to the grid
        spawnX = round(spawnX / 64) * 64;
        // Fit the random number to the grid
        spawnY = round(spawnY / 64) * 64;

        // Update apple position
        tempApple.x = spawnX;
        tempApple.y = spawnY;
    } while (player.collides(&tempApple));

    spawner.spawn(new Apple(spawnX, spawnY));
}

void GameManager::resetGame() {

    // Reset variables
    player.x = 0;
    player.y = 0;
    player.setDirection(DIR_RIGHT);
    while (player.getSize() > 1) {
        player.decreaseSize();
    }
    waitingForInput = false;
    gameOver = false;
    running = true;
    m_tickRate = 0.0f;
    m_spawnRate = 0.0f;

    // Start Music Sound Track
    soundHandler.playMusic(music);

    spawner.cleanUp();
    spawnApple();
}