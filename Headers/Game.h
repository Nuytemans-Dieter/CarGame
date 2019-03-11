//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H


#include "Factories/AbstractFactory.h"

class Game {
public:

    Game(AbstractFactory *aFact);
    void start();
    void gameLoop();
    ~Game();

};


#endif //UNTITLED_GAME_H
