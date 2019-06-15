//
// Created by Dieter on 18/03/2019.
//

#ifndef UNTITLED_SDLBACKGROUND_H
#define UNTITLED_SDLBACKGROUND_H


#include "../../Background.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"

class SDLBackground : public Background{
public:
    SDLBackground(SDLRenderer*);
    ~SDLBackground();
    // Render the background on screen.
    void visualize();
private:
    SDLTexture* texture;
    SDLRenderer* renderer;
};


#endif //UNTITLED_SDLBACKGROUND_H
