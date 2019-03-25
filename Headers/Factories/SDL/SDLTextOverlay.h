//
// Created by Dieter on 25/03/2019.
//

#ifndef UNTITLED_SDLTEXTOVERLAY_H
#define UNTITLED_SDLTEXTOVERLAY_H


#include <SDL2/SDL_ttf.h>
#include "SDLTexture.h"
#include "../TextOverlay.h"
#include "SDLRenderer.h"

class SDLTextOverlay : public TextOverlay {
public:
    SDLTextOverlay(SDLRenderer*);
    ~SDLTextOverlay();

    //Set the position of the text
    void setPosition(int x, int y);
    //Set the text
    void setText(std::string);
    //render the text
    void render();

private:
    int xPosition = 0;
    int yPosition = 0;
    int fontsize;
    TTF_Font* font;
    SDL_Color textColor;
    SDLRenderer* renderer;
    SDLTexture texture;

    void free();
};


#endif //UNTITLED_SDLTEXTOVERLAY_H
