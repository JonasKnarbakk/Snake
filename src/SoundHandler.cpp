#include "SoundHandler.h"
#include <iostream>

SoundHandler::SoundHandler() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        success = false;
    } else {
        success = true;
    }
}

SoundHandler::~SoundHandler() {}

bool SoundHandler::initialized() {
    return success;
}

Mix_Music *SoundHandler::loadMusic(std::string path) {
    // Load in wav file and check if successful
    Mix_Music *musicTrack = Mix_LoadMUS(path.c_str());
    if (musicTrack == nullptr) {
        std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return musicTrack;
}

Mix_Chunk *SoundHandler::loadSFX(std::string path) {
    // Load in wav file and check if successful
    Mix_Chunk *sfx = Mix_LoadWAV(path.c_str());
    if (sfx == nullptr) {
        std::cout << "Failed to load scratch sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return sfx;
}

void SoundHandler::playMusic(Mix_Music *music) {
    // If no music is playing
    if (Mix_PlayingMusic() == 0) {
        // Play the music
        std::cout << "Playing music!" << std::endl;
        Mix_PlayMusic(music, -1);
    }
}

void SoundHandler::stopMusic(Mix_Music *music) {
    // Stop the music from playing
    Mix_HaltMusic();
}

void SoundHandler::playSFX(Mix_Chunk *sfx) {
    Mix_PlayChannel(-1, sfx, 0);
}
