//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_TEXTCAR_H
#define UNTITLED_TEXTCAR_H

#include <iostream>

#include "../../GameObjects/Car.h"

using namespace std;

class TextCar : public Car {

public:
    TextCar();
    void visualize();
    ~TextCar();

};


#endif //UNTITLED_TEXTCAR_H
