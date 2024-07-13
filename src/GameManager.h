/*
 * @file: GameManager.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <11.02.2013>
 *
 * @description: A singleton class to control all gameplay.
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SDL/SDLManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Spawner.h"
#include "SoundHandler.h"
#include "TextHandler.h"

class GameManager {
  public:
    /* Meyer's singleton style instance call */
    static GameManager &Instance() {
        static GameManager g;
        return g;
    }

    /* Kicks off/is the the gameloop */
    void play();

  private:
    GameManager();                               // Hidden constructor
    GameManager(const GameManager &);            // Hidden copy constructor
    GameManager &operator=(const GameManager &); // Hidden assign operator

    unsigned int m_window;        // pointer to main window
    float m_lastRender;           // Time in seconds since last render
    float m_tickRate;             // Time in seconds since last update
    float m_spawnRate;            // Time in seconds since last spawn
    bool gameOver, running;       // Game state
    bool waitingForInput = false; // Flag for when waiting for input at gameover screen

    Spawner spawner;           // Spawner to handle the spawning of game objects
    SoundHandler soundHandler; // Load music and sfx
    TextHandler textHandler;   // Render text to the screen

    // SDL Color definitions
    SDL_Color colorRed;
    SDL_Color colorWhite;

    // SFX
    Mix_Chunk *gameOverSound;

    // The background graphics
    GameObject background;

    // The player
    Player player;

    // Music track
    Mix_Music *music;

    // Manage input
    void input();

    // Do the updates to game mechanics
    void update();

    // Render everything to the screen
    void render();

    // Spawn an apple at a random location
    void spawnApple();

    // Reset the game to play again
    void resetGame();
};

#endif