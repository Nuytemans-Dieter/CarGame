//
// Created by Dieter on 7/04/2019.
//

#include "../../../Headers/Factories/SDL/SDLLaser.h"

SDLLaser::SDLLaser(SDLRenderer * sdlRenderer) {
    renderer = sdlRenderer;
    texture = new SDLTexture();
    texture->loadImage("laser.png",renderer->getSDL_Renderer());
    setWidth(texture->getWidth()); setHeight(texture->getHeight());
}

SDLLaser::~SDLLaser() {
    texture->free();
}

void SDLLaser::visualize() {
    renderer->render(texture, getXPos(), getYPos());
}
