//
// Created by Dieter on 4/03/2019.
//

#include "../Headers/Game.h"
#include "../Headers/GameObjects/Car.h"
#include "../Headers/Background.h"

Game::Game(AbstractFactory *aFact) {
    factory = aFact;
    gameLoop();
}

void Game::Game::start() {
    //Move objects

    //Collision detection

    //Visualize
}

void Game::gameLoop() {
    bool playing = true;
    Background* bg = factory->createBackground();
    Car* car = factory->createCar(Car::RED);
    car->setXPos(95);
    car->setYPos(640);

    while (playing)
    {
        //Move objects
        car->setYPos(car->getYPos()-1);
        bg->moveDown(1);

        //Collision detection

        //visualize
        factory->startRendering();
        bg->visualize();
        car->visualize();
        factory->finishRendering();
    }
}

Game::~Game() {

}
