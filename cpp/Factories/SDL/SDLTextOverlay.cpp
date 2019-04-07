

#include "../../../Headers/Factories/SDL/SDLTextOverlay.h"


SDLTextOverlay::SDLTextOverlay(SDLRenderer* rend) {
    renderer = rend;
    fontsize = 15;
    textColor = { 215, 11 , 11}; //RED


    //Open the font
    font = TTF_OpenFont( "..//Resources//Fonts//roundFont.ttf", fontsize );
//    font = TTF_OpenFont( "..//Resources//Fonts//pixelFont.ttf", fontsize );
    if( font == NULL )
    {
        printf( "SDL_ttf Error: %s\n", TTF_GetError() );
    }


    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "5" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

}

SDLTextOverlay::~SDLTextOverlay() {
    free();
}

void SDLTextOverlay::setPosition(int x, int y) {
    xPosition = x; yPosition = y;
}

void SDLTextOverlay::free() {
    if (texture.getTexture() != NULL)
    {
        SDL_DestroyTexture(texture.getTexture());
        texture.free();
    }
}

void SDLTextOverlay::setText(std::string txt) {
    //Get rid of preexisting texture
    free();

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, txt.c_str(), textColor);

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer->getSDL_Renderer(), surfaceMessage);

    texture.setTexture(message, surfaceMessage->h, surfaceMessage->w);

}

void SDLTextOverlay::render() {
    renderer->render(&texture, xPosition, yPosition);
}

//
// Created by Dieter on 25/03/2019.
//

#include "../../../Headers/Factories/SDL/SDLTextOverlay.h"
