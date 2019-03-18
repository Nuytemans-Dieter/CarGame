

#include "../../../Headers/Factories/SDL/SDLBackground.h"


SDLBackground::SDLBackground(SDLRenderer * rendererIn) {
    renderer = rendererIn;
    texture = new SDLTexture();
    texture->loadImage("..//resources//road2.png", renderer->getSDL_Renderer());
}

void SDLBackground::visualize() {
    renderer->render(texture, 0, getLocation());
}

SDLBackground::~SDLBackground() {

}

//
// Created by Dieter on 18/03/2019.
//

#include "../../../Headers/Factories/SDL/SDLBackground.h"
