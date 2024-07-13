// Description: New Class
// Created by Jonas Knarbakk (00:08:40-25/03/2017)

#include "MusicHandler.hpp"
#include <SDL.h>

MusicHandler::MusicHandler() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

MusicHandler::~MusicHandler() {
    if (m_soundTrack != NULL) {
        Mix_FreeMusic(m_soundTrack);
    }
}

bool MusicHandler::loadMusicTrack(std::string path) {
    m_soundTrack = Mix_LoadMUS(path.c_str());

    if (m_soundTrack == NULL) {
        printf("Could not load track: %s\n", path.c_str());
        return false;
    }
    return true;
}

bool MusicHandler::start() {
    if (Mix_PlayingMusic() == false) {
        if (Mix_PlayMusic(m_soundTrack, -1) == -1) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool MusicHandler::play() {
    if (Mix_PausedMusic() == true) {
        Mix_ResumeMusic();
        return true;
    }
    return false;
}
bool MusicHandler::pause() {
    if (Mix_PausedMusic() == false) {
        Mix_PauseMusic();
        return true;
    }
    return false;
}

bool MusicHandler::stop() {
    Mix_HaltMusic();
    return true;
}
