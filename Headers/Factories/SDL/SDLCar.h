//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_SDLCAR_H
#define UNTITLED_SDLCAR_H


#include "../../GameObjects/Car.h"
#include "SDLTexture.h"
#include "SDLRenderer.h"

class SDLCar : public Car {
public:
    //Create a Car with default color
    SDLCar(SDLRenderer*);
    //Create a Car with a chosen color
    SDLCar(SDLRenderer*, Color);
    ~SDLCar();

    std::string getImagePath();

    void visualize();

private:
    //Initialize car fields
    void prepare(SDLRenderer*, Color);

    SDLTexture* texture;
    SDLRenderer* renderer;
    Color* carColor;
};


#endif //UNTITLED_SDLCAR_H
