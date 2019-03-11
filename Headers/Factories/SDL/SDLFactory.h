//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_SDLFACTORY_H
#define UNTITLED_SDLFACTORY_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../../Car.h"
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

     /**
      * get an SDL_Surface from a given path (starting in the resources folder)
      * Only works with .BMP resources
      * Remember to use double '/' in the path! Example/test.bmp is not correct.
      * Use '//' instead! Example//test.bmp is correct.
      * @param path to the wanted resource
      * @return SDL_Surface, loaded from a .BMP file
      */
     SDL_Surface getBmpResource(std::string path);

     bool load();

};


#endif //UNTITLED_SDLFACTORY_H
