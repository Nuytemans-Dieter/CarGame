//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_CAR_H
#define UNTITLED_CAR_H


#include "GameObject.h"

class Car : public GameObject{

public:
    enum Color {
        BLACK,
        BLUE,
        GREY,
        WHITE,
        GREEN,
        RED
    };

    Car();
    // Visualize the Car on screen.
    virtual void visualize() = 0;
    ~Car();
};


#endif //UNTITLED_CAR_H
