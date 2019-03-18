//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_SDLFACTORY_H
#define UNTITLED_SDLFACTORY_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../../GameObjects/Car.h"
#include "../AbstractFactory.h"
#include "SDLCar.h"
#include "SDLTexture.h"

class SDLFactory : public AbstractFactory {
public:
    SDLFactory();
    ~SDLFactory();

    /**
     * Creates the game screen on which the objects will be drawn
     */
    bool init();

    /**
     * Closes the created game screen
     */
    void close();

    /**
     * Various methods to create a visual representation of game objects
     */
     Car* createCar();
     Car* createCar(SDLCar::Color);
     Background* createBackground();

     void startRendering();
     void finishRendering();

     bool load();
private:
    SDL_Renderer* renderer;
    SDLRenderer* renderHandler;
};


#endif //UNTITLED_SDLFACTORY_H
