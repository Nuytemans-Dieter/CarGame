

#include "../../../Headers/Sound/SDL/SDLSound.h"


SDLSound::SDLSound() {

}

SDLSound::~SDLSound() {
    free();
}

void SDLSound::loadSound(Sound::sound name) {
    Mix_FreeChunk(sound);
    sound = Mix_LoadWAV(getSoundPath(name).c_str());
    if (sound == NULL)
    {
        printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void SDLSound::playSound() {
    Mix_PlayChannel(-1, sound, 0);
}

void SDLSound::loadMusic(Sound::music name) {
    Mix_FreeMusic(song);
    song = Mix_LoadMUS(getSongPath(name).c_str());
    if (song == NULL)
    {
        printf( "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void SDLSound::playMusicLoop() {
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(song, -1);
    }
}

std::string SDLSound::getSoundPath(Sound::sound name) {
    std::string path = "..//Resources//Sounds//";
    switch(name) {
        case Sound::shoot:      path.append("laser");       break;
        case Sound::explosion:  path.append("explosion");   break;
        case Sound::speedup:    path.append("speedup");     break;
        case Sound::invincible: path.append("invincible");  break;
        case Sound::powerup:    path.append("powerup");     break;
    }
    path.append(".wav");
    return path;
}

std::string SDLSound::getSongPath(Sound::music name) {
    std::string path = "..//Resources//Music//track";
    switch (name)
    {
        case Sound::track1: path.append("1"); break;
        case Sound::track2: path.append("2"); break;
        case Sound::track3: path.append("3"); break;
        case Sound::track4: path.append("4"); break;
        case Sound::track5: path.append("5"); break;
        case Sound::track6: path.append("6"); break;
        case Sound::track7: path.append("7"); break;
        case Sound::track8: path.append("8"); break;
        case Sound::track9: path.append("9"); break;
        case Sound::track10:path.append("10");break;
    }
    path.append(".wav");
    return path;
}

void SDLSound::free()
{
    Mix_FreeChunk(sound);
    Mix_FreeMusic(song);
}

//
// Created by Dieter on 7/04/2019.
//

#include "../../../Headers/Sound/SDL/SDLSound.h"
