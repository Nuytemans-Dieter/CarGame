//
// Created by Dieter on 18/03/2019.
//

#include "../../Headers/GameObjects/GameObject.h"
GameObject::GameObject() {
    xPos = 0; yPos = 0;
    width = 0; height = 0;
    xVelocity = 0; yVelocity = 0;

    //Boundaries
    xMin = 0; yMin = 0;
    xMax = 0; yMax = 0;
}
GameObject::~GameObject() {}

int GameObject::getXPos() {
    return xPos;
}

int GameObject::getYPos() {
    return yPos;
}

void GameObject::setWidth(int w) {
    width = w;
}

void GameObject::setHeight(int h) {
    height = h;
}

int GameObject::getWidth() {
    return width;
}

int GameObject::getHeight() {
    return height;
}


bool GameObject::isColliding(GameObject * obj) {

    if (yPos + height <= obj->getYPos())            return false;

    if (yPos >= obj->getYPos() + obj->getHeight())  return false;

    if (xPos + width <= obj->getXPos())             return false;

    if (xPos >= obj->getXPos() + obj->getWidth())   return false;

    return true;
}

void GameObject::updateLocation() {
    setXPos(xPos + xVelocity);
    setYPos(yPos + yVelocity);
}

void GameObject::setYVelocity(int yVel) {
    yVelocity = yVel;
}

void GameObject::setXVelocity(int xVel) {
    xVelocity = xVel;
}

void GameObject::setXPos(int x) {
    if (xMax != 0 && x + width > xMax)
        xPos = xMax - width;
    else if (xMin != 0 && x < xMin)
        xPos = xMin;
    else xPos = x;
}

void GameObject::setYPos(int y) {
    if (yMax != 0 && y + height > yMax)
        yPos = yMax - height;
    else if (yMin != 0 && y < yMin)
        yPos = yMin;
    else yPos = y;
}

void GameObject::setBoundaries(int minX, int minY, int maxX, int maxY) {
    xMin = minX; yMin = minY;
    xMax = maxX; yMax = maxY;
}
