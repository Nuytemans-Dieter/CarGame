

#include "../Headers/Background.h"


Background::Background() {
    resetLocationY = 0;
    location = 0;
}

int Background::getLocation() {
    return location;
}

void Background::setResetLocation(int y) {
    resetLocationY = y;
}

void Background::resetLocation() {
//    location = -640 + 48;
    location = resetLocationY;
}

void Background::moveDown(int x) {
    location = location + x;
}

Background::~Background() {

}

#include "../Headers/Background.h"
