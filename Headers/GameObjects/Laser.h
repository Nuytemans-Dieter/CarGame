//
// Created by Dieter on 7/04/2019.
//

#ifndef UNTITLED_LASER_H
#define UNTITLED_LASER_H


#include "GameObject.h"

class Laser : public GameObject {
public:
    Laser();
    // Visualize the laser on screen.
    virtual void visualize() = 0;
    ~Laser();
};


#endif //UNTITLED_LASER_H
