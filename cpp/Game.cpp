//
// Created by Dieter on 4/03/2019.
//

#include <iostream>
#include <list>
#include "../Headers/Game.h"
#include "../Headers/GameObjects/Car.h"
#include "../Headers/Background.h"

Game::Game(AbstractFactory *aFact, AbstractEventReader *aEvent) {
    factory = aFact;
    eventReader = aEvent;
    gameLoop();
}

void Game::Game::start() {
    //Move objects

    //Collision detection

    //Visualize
}

void Game::gameLoop() {
    bool isPlaying = true;
    int playerVelocity = 3;
    int points = 0;

    std::list<Car*> cars;

    TextOverlay* score = factory->createTextOverlay();
    score->setPosition(1,10);

    TextOverlay* lives = factory->createTextOverlay();
    lives->setPosition(600,10);
    lives->setText("Lives: 3");

    Background* bg = factory->createBackground();
    bg->setResetLocation(-592);
    bg->resetLocation();

    Car* car = factory->createCar(Car::RED);
    car->setXPos(95); car->setYPos(400);
    car->setBoundaries(80,250,560,640);
    cars.push_front(car);

    Car* c = factory->createCar(Car::BLUE);
    c->setXPos(120); c->setYPos(-350);
    c->setYVelocity(2);
    cars.push_back(c);

    while (isPlaying)
    {
        /**
         * Move objects
         */
        score->setText("Score: " + std::to_string(points));
        points++;


        //Read input
        switch (eventReader->getCurrentEvent()) {
            case AbstractEventReader::WINDOW_CLOSE:
                factory->quit();
                isPlaying = false;
                break;
            case AbstractEventReader::ARROW_LEFT:
                car->setXVelocity(-playerVelocity);     break;
            case AbstractEventReader::ARROW_RIGHT:
                car->setXVelocity(playerVelocity);      break;
            case AbstractEventReader::ARROW_UP:
                car->setYVelocity( -playerVelocity );   break;
            case AbstractEventReader::ARROW_DOWN:
                car->setYVelocity( playerVelocity );    break;
            case AbstractEventReader::NONE:
                car->setXVelocity(0);
                car->setYVelocity(0);
                break;
//            case AbstractEventReader::ESC:
        }

        //Handle background
        bg->moveDown(8);
        if (bg->getLocation() >= 0) bg->resetLocation();


        //Move the car
//        for(std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++)
//        {
//
//        }
        car->updateLocation();
        c->updateLocation();

        if (c->getYPos() == 640)
            c->setYPos(-250);

        /**
         * Collision detection
         */
        if (car->isColliding(c))
        {
            factory->quit(); isPlaying = false;
        }

        /**
         * Visualize
         */
        factory->startRendering();

        bg->visualize();
        car->visualize();
        c->visualize();

        score->render();
        lives->render();

        factory->finishRendering();
    }
}

Game::~Game() {

}
