//
// Created by Dieter on 4/03/2019.
//

#include "../../../Headers/Factories/SDL/SDLCar.h"



void SDLCar::visualize() {
    renderer->render(texture, getXPos(), getYPos());
}

SDLCar::SDLCar(SDLRenderer* rendererIn) {
    prepare(rendererIn, RED);
}

SDLCar::SDLCar(SDLRenderer* rendererIn, Color color)
{
    prepare(rendererIn,color);
    setWidth(texture->getWidth());
    setHeight(texture->getHeight());
}

void SDLCar::prepare(SDLRenderer* rendererIn, Color color)
{
    carColor = &color;
    renderer = rendererIn;
    texture = new SDLTexture();
    texture->loadImage(getImagePath(), renderer->getSDL_Renderer());
}

std::string SDLCar::getImagePath() {
    std::string filePath = "Cars//";
    switch(*carColor)
    {
        case BLACK:
            filePath.append("black");
            break;
        case BLUE:
            filePath.append("blue");
            break;
        case GREY:
            filePath.append("grey");
            break;
        case WHITE:
            filePath.append("white");
            break;
        case GREEN:
            filePath.append("green");
            break;
        default: //Red
            filePath.append("red");
    }
    filePath.append("CarSmall.png");

    return filePath;
}

SDLCar::~SDLCar() {
    texture->free();
}
