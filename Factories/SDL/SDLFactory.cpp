//
// Created by Dieter on 4/03/2019.

#include "../../Headers/Factories/SDL/SDLFactory.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window;
SDL_Surface* windowSurface;
SDL_Surface* car;

SDLFactory::SDLFactory() {
    window = NULL;
    windowSurface = NULL;
    car = NULL;

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
        SDLTexture* car = new SDLTexture(window, renderer);
        car->loadImage("Cars//greyCar.png");
        car->render(0,0);
        SDL_Delay(1000);
        //Load media
//        if( !load() )
//        {
//            printf( "Failed to load media!\n" );
//        }
//        else
//        {
//            //Apply the image
//            SDL_BlitSurface( car, NULL, windowSurface, NULL );
//
//            //Update the surface
//            SDL_UpdateWindowSurface( window );
//
//            //Wait two seconds
//            SDL_Delay( 2000 );
//        }
    }

    //SDLTexture* texture = new SDLTexture(window, renderer);

    //Free resources and close SDL
    close();
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

bool SDLFactory::load()
{
    bool success = true;
    car = SDL_LoadBMP( "..//Resources//Cars//redCarSmall.bmp" );
    if( car == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "Resources/Cars/redCar.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void SDLFactory::close() {
    //Deallocate surface
    SDL_FreeSurface( car );
    car = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

Car* SDLFactory::createCar() {
    return new SDLCar();
}

SDLFactory::~SDLFactory() {
    close();
}

SDL_Surface SDLFactory::getBmpResource(std::string path) {

//    SDL_Surface bmp = NULL;
//    bmp = SDL_LoadBMP( path );
//
//    if( bmp == NULL )
//    {
//        printf( "Unable to load image %s! SDL Error: %s\n", fullPath, SDL_GetError() );
//    }
//
//    return bmp;

}
