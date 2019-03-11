//
// Created by Dieter on 4/03/2019.
//

#include "Headers/Game.h"

Game::Game(AbstractFactory *aFact) {
    Car *c = aFact->createCar();
    c->visualize();
}


void Game::Game::start() {
    //Move objects

    //Collision detection

    //Visualize
}

void Game::gameLoop() {
    bool playing = true;
    while (playing)
    {
        //Move objects

        //Collision detection

        //visualize
    }
}

Game::~Game() {

}
