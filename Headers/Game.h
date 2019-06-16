//
// Created by Dieter on 4/03/2019.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H


#include "Factories/AbstractFactory.h"
#include "Events/AbstractEventReader.h"

class Game {
public:
    // Singleton pattern -> get this object if it exist, otherwise create it.
    static Game *getInstance(AbstractFactory *, AbstractEventReader *);

    // This will start the game loop.
    void gameLoop();

    ~Game();

private:
    static Game *instance;
    AbstractFactory *factory;
    AbstractEventReader *eventReader;

    // Create an instance of Game with a given factory and eventreader.
    Game(AbstractFactory *, AbstractEventReader *);
};


#endif //UNTITLED_GAME_H
