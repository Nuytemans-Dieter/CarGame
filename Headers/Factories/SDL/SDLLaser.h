//
// Created by Dieter on 7/04/2019.
//

#ifndef UNTITLED_SDLLASER_H
#define UNTITLED_SDLLASER_H


#include "../../GameObjects/Laser.h"
#include "SDLRenderer.h"

class SDLLaser : public Laser{
public:
    SDLLaser(SDLRenderer*);
    ~SDLLaser();

    // Render the laser on screen.
    void visualize();

private:
    SDLTexture* texture;
    SDLRenderer* renderer;
};


#endif //UNTITLED_SDLLASER_H
