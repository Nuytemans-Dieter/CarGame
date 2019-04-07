//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_ABSTRACTFACTORY_H
#define UNTITLED_ABSTRACTFACTORY_H


#include "../GameObjects/Car.h"
#include "SDL/SDLRenderer.h"
#include "../Background.h"
#include "TextOverlay.h"
#include "SDL/SDLTextOverlay.h"
#include "../GameObjects/Laser.h"
#include "../Sound/Sound.h"

class AbstractFactory {
public:
    AbstractFactory();

    virtual Car* createCar()=0;
    virtual Car* createCar(Car::Color)=0;
    virtual Laser* createLaser()=0;
    virtual Background* createBackground()=0;
    virtual TextOverlay* createTextOverlay()=0;
    virtual TextOverlay* createTextOverlay(int) = 0; //creates a text overlay with given pixel height
    virtual Sound* createSound()=0;

    //Prepare tasks that must happen before the render process (ex. clear the screen)
    virtual void startRendering()=0;
    //Perform final tasks after rendering, including a delay (if needed)
    virtual void finishRendering()=0;
    //Destroy everything related to the factory
    virtual void quit()=0;
    ~AbstractFactory();
};


#endif //UNTITLED_ABSTRACTFACTORY_H
