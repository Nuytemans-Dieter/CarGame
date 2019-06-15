//
// Created by Dieter on 8/04/2019.
//

#ifndef UNTITLED_POWERUP_H
#define UNTITLED_POWERUP_H


#include "GameObject.h"

class Powerup : public GameObject {

public:
    enum PowerupType {
        HEALTH,
        AMMO,
        BOMB
    };

    // Create a Powerup of given type.
    Powerup(PowerupType);
    // Render this Powerup on screen
    virtual void visualize() = 0;

    Powerup();
    ~Powerup();

};


#endif //UNTITLED_POWERUP_H
