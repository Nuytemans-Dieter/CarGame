//
// Created by Dieter on 8/04/2019.
//

#ifndef UNTITLED_SDLPOWERUP_H
#define UNTITLED_SDLPOWERUP_H


#include "../../GameObjects/Powerup.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"

class SDLPowerup : public Powerup {
public:
    // Create a Powerup with a custom renderer and a powerup type
    SDLPowerup(SDLRenderer*, Powerup::PowerupType);
    // Render the Powerup on screen.
    void visualize();
    SDLPowerup();
    ~SDLPowerup();

private:
    SDLTexture* texture;
    SDLRenderer* renderer;

};


#endif //UNTITLED_SDLPOWERUP_H
