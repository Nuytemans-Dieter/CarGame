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
        FORCEFIELD
    };

    // Create a Powerup of given type.
    Powerup(PowerupType);
    // Render this Powerup on screen.
    virtual void visualize() = 0;
    // Set the type of this Powerup.
    void setPowerup(PowerupType);
    // Get the type of this Powerup
    PowerupType getPowerup();
    Powerup();
    ~Powerup();
private:
    PowerupType type;
};


#endif //UNTITLED_POWERUP_H
