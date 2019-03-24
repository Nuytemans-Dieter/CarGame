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
};


#endif //UNTITLED_GAME_H
