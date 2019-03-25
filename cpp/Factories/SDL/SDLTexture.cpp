//
// Created by Dieter on 11/03/2019.
//

#include "../../../Headers/Factories/SDL/SDLTexture.h"

SDLTexture::SDLTexture() {
    texture = NULL;
    width = 0;
    height = 0;
}

SDLTexture::~SDLTexture() {
    free();
}

bool SDLTexture::loadImage(std::string path, SDL_Renderer* renderer) {
    free(); //Clear the current image

    std::string fullPath = "..//resources//";
    fullPath.append(path);

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( fullPath.c_str() );

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ));
    }

    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface);
    if (newTexture == NULL)
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    } else
    {
        width = loadedSurface->w;
        height = loadedSurface->h;
    }

    SDL_FreeSurface( loadedSurface );

    texture = newTexture;
    return texture != NULL;
}

void SDLTexture::setTexture(SDL_Texture * newTexture, int h, int w) {
    free();
    height = h; width = w;
    texture = newTexture;
}


void SDLTexture::free() {
    if (texture != NULL)
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
        width = 0;
        height = 0;
    }
}

int SDLTexture::getWidth() {
    return width;
}

int SDLTexture::getHeight() {
    return height;
}

SDL_Texture* SDLTexture::getTexture() {
    return texture;
}
