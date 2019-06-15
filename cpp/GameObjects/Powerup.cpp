//
// Created by Dieter on 8/04/2019.
//

#include "../../Headers/GameObjects/Powerup.h"

Powerup::Powerup() {

}

Powerup::~Powerup() {

}

Powerup::PowerupType Powerup::getPowerup() {
    return type;
}

void Powerup::setPowerup(Powerup::PowerupType powerupType) {
    type = powerupType;
}
