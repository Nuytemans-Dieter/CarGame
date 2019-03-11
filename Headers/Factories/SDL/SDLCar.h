//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_SDLCAR_H
#define UNTITLED_SDLCAR_H


#include "../../Car.h"

class SDLCar : public Car {
public:
    SDLCar();
    ~SDLCar();

    void visualize() override;


};


#endif //UNTITLED_SDLCAR_H
