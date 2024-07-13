#pragma once

#include <vector>
#include <string>
#include <SDL_mixer.h>

class SoundHandler {
  public:
    SoundHandler();
    ~SoundHandler();

    // returns true if the sound handler got initialized properly
    bool initialized();

    // Loads a wav file from path
    Mix_Music *loadMusic(std::string path);

    // Load a wav file from path
    Mix_Chunk *loadSFX(std::string path);

    // Play a Mix_Music object
    void playMusic(Mix_Music *music);

    // Stop a Mix_Music object
    void stopMusic(Mix_Music *music);

    // Play a Mix_Chunk object
    void playSFX(Mix_Chunk *sfx);

  private:
    bool success;
};