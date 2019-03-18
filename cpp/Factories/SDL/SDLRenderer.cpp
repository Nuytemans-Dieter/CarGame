//
// Created by Dieter on 18/03/2019.
//

#include <cmath>
#include "../../../Headers/Factories/SDL/SDLRenderer.h"

SDLRenderer::SDLRenderer(SDL_Renderer* renderer1) {
    renderer = renderer1;
}
SDLRenderer::~SDLRenderer() {}

void SDLRenderer::render(SDLTexture* texture, int x, int y) {
    render(texture, x, y, 1);
}

void SDLRenderer::render(SDLTexture* texture, int x, int y, double resize) {
    SDL_Rect renderQuad = {x, y, (int) std::round(texture->getWidth()*resize), (int) std::round(texture->getHeight()*resize)};
    SDL_RenderCopy(renderer, texture->getTexture(), NULL, &renderQuad);
}

SDL_Renderer *SDLRenderer::getSDL_Renderer() {
    return renderer;
}