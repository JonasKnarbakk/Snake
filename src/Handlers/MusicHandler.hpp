#ifndef MUSICHANDLER_HPP
#define MUSICHANDLER_HPP

#include <SDL2/SDL_mixer.h>
#include <string>

class MusicHandler{
    private:
        Mix_Music *m_soundTrack;
    public:
        MusicHandler();
        ~MusicHandler();

        // Load a music file
        bool loadMusicTrack(std::string path);

        // Start the music
        bool start();

        // Play the music if paused
        bool play();
        
        // Pause the music if playing
        bool pause();
        
        // Stop the music from playing
        bool stop();
};

#endif
