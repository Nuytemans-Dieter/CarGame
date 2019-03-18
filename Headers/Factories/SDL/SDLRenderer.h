//
// Created by Dieter on 18/03/2019.
//

#ifndef UNTITLED_SDLRENDERER_H
#define UNTITLED_SDLRENDERER_H


#include <string>
#include "SDLTexture.h"

class SDLRenderer {
public:
    SDLRenderer(SDL_Renderer*);
    ~SDLRenderer();

    //Render a given texture at the given location
    void render(SDLTexture*, int x, int y);
    //Render a given texture at the given location and resize the image with the given factor
    void render(SDLTexture*, int x, int y, double resize);
    SDL_Renderer* getSDL_Renderer();

private:
    SDL_Renderer* renderer;

};


#endif //UNTITLED_SDLRENDERER_H
