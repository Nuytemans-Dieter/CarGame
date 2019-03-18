

#include "../Headers/Background.h"


Background::Background() {
    location = -640;
}

int Background::getLocation() {
    return location;
}

void Background::moveDown(int x) {
    location = location + x;
}

Background::~Background() {

}

//
// Created by Dieter on 18/03/2019.
//

#include "../Headers/Background.h"
