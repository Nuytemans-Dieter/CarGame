//
// Created by Dieter on 4/03/2019.
//

#include "../../../Headers/Factories/Text/TextFactory.h"


Car* TextFactory::createCar() {
    return new TextCar();
}

TextFactory::~TextFactory() {

}

TextFactory::TextFactory() {

}
