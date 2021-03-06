//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_SDLFACTORY_H
#define UNTITLED_SDLFACTORY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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

    // Creates the game screen on which the objects will be drawn.
    bool init();

     // -------
     // Various methods to create a visual representation of the game object mentioned in the function name.
     // -------
     Car* createCar();                   // Default color will be used.
     Car* createCar(Car::Color);         // Pick your own color.
     Laser* createLaser();
     Powerup* createPowerup(Powerup::PowerupType);
     Background* createBackground();
     TextOverlay* createTextOverlay();
     TextOverlay* createTextOverlay(int); // Creates text overlay with a given pixel height.
     Sound* createSound();

     // Close everything.
     void quit();

     // Render a message on a specified location.
     void renderMessage(std::string, int x, int y);

     // Clear the screen so that a new scene can be drawn.
     void startRendering();
     // Update the renderer.
     void finishRendering();

private:
    SDL_Renderer* renderer;
    SDLRenderer* renderHandler;
};


#endif //UNTITLED_SDLFACTORY_H
