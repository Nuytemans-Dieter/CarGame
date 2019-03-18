//
// Created by Dieter on 4/03/2019.

#include <cmath>
#include "../../../Headers/Factories/SDL/SDLFactory.h"
#include "../../../Headers/Factories/SDL/SDLBackground.h"

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
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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
    return success;
}

void SDLFactory::close() {
    //Destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

Car* SDLFactory::createCar() {
    return new SDLCar(renderHandler);
}

Car* SDLFactory::createCar(SDLCar::Color color) {
    return new SDLCar(renderHandler, color);
}

Background* SDLFactory::createBackground()
{
    return new SDLBackground(renderHandler);
}

SDLFactory::~SDLFactory() {
    close();
}

void SDLFactory::startRendering() {
    SDL_RenderClear(renderer);
}

void SDLFactory::finishRendering() {
    SDL_RenderPresent(renderer);
    SDL_Delay(20);
}