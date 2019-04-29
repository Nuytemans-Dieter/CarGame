//
// Created by Dieter on 7/04/2019.
//

#ifndef UNTITLED_SDLSOUND_H
#define UNTITLED_SDLSOUND_H


#include <string>
#include <SDL2/SDL_mixer.h>

#include "../Sound.h"

class SDLSound : public Sound{
public:
    SDLSound();
    ~SDLSound();

    void loadSound(Sound::sound);
    void playSound();

    void loadMusic(Sound::music);
    void playMusicLoop();

    void free();

private:
    Mix_Music *song = NULL;
    Mix_Chunk *sound = NULL;

    std::string getSoundPath(Sound::sound);
    std::string getSongPath(Sound::music);
};


#endif //UNTITLED_SDLSOUND_H
