//
// Created by Dieter on 4/03/2019.

#include <cmath>
#include "../../../Headers/Factories/SDL/SDLFactory.h"
#include "../../../Headers/Factories/SDL/SDLBackground.h"
#include "../../../Headers/Factories/SDL/SDLLaser.h"
#include "../../../Headers/Sound/Sound.h"
#include "../../../Headers/Sound/SDL/SDLSound.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

SDL_Window* window;
SDL_Surface* windowSurface;

SDLFactory::SDLFactory() {
    window = NULL;
    windowSurface = NULL;

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        renderer = SDL_CreateRenderer(window,-1,0);
        renderHandler = new SDLRenderer(renderer);
    }
}

bool SDLFactory::init() {
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            windowSurface = SDL_GetWindowSurface( window );
        }
    }

    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void SDLFactory::quit() {
    //Destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}

Car* SDLFactory::createCar() {
    return SDLFactory::createCar(SDLCar::RED);
}

Car* SDLFactory::createCar(SDLCar::Color color) {
    Car* c = new SDLCar(renderHandler, color);
    return c;
}

Laser* SDLFactory::createLaser()
{
    Laser* l = new SDLLaser(renderHandler);
    return l;
}

TextOverlay *SDLFactory::createTextOverlay() {
    TextOverlay* to = new SDLTextOverlay(renderHandler);
    return to;
}

TextOverlay *SDLFactory::createTextOverlay(int height) {
    TextOverlay* to = new SDLTextOverlay(renderHandler, height);
    return to;
}

Sound* SDLFactory::createSound() {
    Sound* s = new SDLSound();
    return s;
}

Background* SDLFactory::createBackground()
{
    return new SDLBackground(renderHandler);
}

SDLFactory::~SDLFactory() {
    quit();
}

void SDLFactory::startRendering() {
    SDL_RenderClear(renderer);
}

void SDLFactory::finishRendering() {
    SDL_RenderPresent(renderer);
}