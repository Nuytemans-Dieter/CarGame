//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_ABSTRACTFACTORY_H
#define UNTITLED_ABSTRACTFACTORY_H


#include "../GameObjects/Car.h"
#include "SDL/SDLRenderer.h"
#include "../Background.h"

class AbstractFactory {
public:
    AbstractFactory();
    virtual Car* createCar()=0;
    virtual Car* createCar(Car::Color)=0;
    virtual Background* createBackground()=0;
    //Prepare tasks that must happen before the render process
    virtual void startRendering()=0;
    //Perform final tasks after rendering
    virtual void finishRendering()=0;
    ~AbstractFactory();
};


#endif //UNTITLED_ABSTRACTFACTORY_H
