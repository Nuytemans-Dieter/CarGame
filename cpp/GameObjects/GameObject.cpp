//
// Created by Dieter on 18/03/2019.
//

#include "../../Headers/GameObjects/GameObject.h"
    GameObject::GameObject() {}
    GameObject::~GameObject() {}

int GameObject::getXPos() {
    return xPos;
}

int GameObject::getYPos() {
    return yPos;
}

void GameObject::setXPos(int x) {
    xPos = x;
}

void GameObject::setYPos(int y) {
    yPos = y;
}
