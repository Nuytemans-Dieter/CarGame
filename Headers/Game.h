//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H


#include "Factories/AbstractFactory.h"
#include "Events/AbstractEventReader.h"

class Game {
public:

    Game(AbstractFactory*, AbstractEventReader*);
    void start();
    void gameLoop();
    ~Game();

private:
    AbstractFactory *factory;
    AbstractEventReader *eventReader;
    //Remove the Car with given ID from the list, and update the 'amount of cars'-variable
    void removeCar(int, Car* cars[]);
};


#endif //UNTITLED_GAME_H
