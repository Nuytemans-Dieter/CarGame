//
// Created by Dieter on 8/04/2019.
//

#include "../../../Headers/Factories/SDL/SDLPowerup.h"

SDLPowerup::SDLPowerup(SDLRenderer* rendererIn, Powerup::PowerupType powerupType) {
    renderer = rendererIn;
    setPowerup(powerupType);

    texture = new SDLTexture();
    std::string imagePath = "Powerups//";
    switch(powerupType)
    {
        case PowerupType::AMMO:
            imagePath.append("ammo");
            break;
        case PowerupType::HEALTH:
            imagePath.append("health");
            break;
        case PowerupType::BOMB:
            imagePath.append("bomb");
            break;
    }
    imagePath.append(".png");
    texture->loadImage(imagePath, renderer->getSDL_Renderer());
    setWidth(texture->getWidth());
    setHeight(texture->getHeight());
}


SDLPowerup::~SDLPowerup() {

}

void SDLPowerup::visualize() {
    renderer->render(texture, getXPos(), getYPos());
}

SDLPowerup::SDLPowerup() {

}


