//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_TEXTFACTORY_H
#define UNTITLED_TEXTFACTORY_H


#include "../AbstractFactory.h"
#include "TextCar.h"

class TextFactory : public AbstractFactory {

public:
    TextFactory();
    Car* createCar();
    ~TextFactory();
};


#endif //UNTITLED_TEXTFACTORY_H
