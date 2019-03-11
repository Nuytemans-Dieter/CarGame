//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_ABSTRACTFACTORY_H
#define UNTITLED_ABSTRACTFACTORY_H


#include "../Car.h"

class AbstractFactory {
public:
    AbstractFactory();
    virtual Car* createCar()=0;
    ~AbstractFactory();
};


#endif //UNTITLED_ABSTRACTFACTORY_H
