//
// Created by Dieter on 4/03/2019.
//

#include <iostream>
#include <list>
#include "../Headers/Game.h"
#include "../Headers/GameObjects/Car.h"
#include "../Headers/Background.h"
#include "../Headers/Chrono.h"

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
    int playerVelocity = 5;
    int points = 0;

    Chrono* chron = new Chrono();

    std::list<Car*> cars;

    TextOverlay* score = factory->createTextOverlay();
    score->setPosition(1,10);

    TextOverlay* lives = factory->createTextOverlay();
    lives->setPosition(565,10);
    lives->setText("Lives: 3");

    Background* bg = factory->createBackground();
    bg->setResetLocation(-592);
    bg->resetLocation();

    Car* player = factory->createCar(Car::RED);
    player->setXPos(95); player->setYPos(400);
    player->setBoundaries(80,250,560,640);
    cars.push_front(player);

    Car* c = factory->createCar(Car::GREEN);
    c->setXPos(100); c->setYPos(-250);
    int cSpeed = 3;
    c->setYVelocity(cSpeed);

    while (isPlaying)
    {
        chron->startTime();
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
            case AbstractEventReader::LEFT:
                player->setXVelocity(-playerVelocity);     break;
            case AbstractEventReader::RIGHT:
                player->setXVelocity(playerVelocity);      break;
            case AbstractEventReader::UP:
                player->setYVelocity( -playerVelocity );   break;
            case AbstractEventReader::DOWN:
                player->setYVelocity( playerVelocity );    break;
            case AbstractEventReader::UPRIGHT:
                player->setXVelocity( playerVelocity );
                player->setYVelocity( - playerVelocity );    break;
            case AbstractEventReader::UPLEFT:
                player->setXVelocity( - playerVelocity );
                player->setYVelocity( - playerVelocity );    break;
            case AbstractEventReader::DOWNRIGHT:
                player->setXVelocity( playerVelocity );
                player->setYVelocity( playerVelocity );    break;
            case AbstractEventReader::DOWNLEFT:
                player->setXVelocity( - playerVelocity );
                player->setYVelocity( playerVelocity );    break;
            case AbstractEventReader::NONE:
                player->setXVelocity(0);
                player->setYVelocity(0);
                break;
//            case AbstractEventReader::ESC:
        }

        //Handle background
        bg->moveDown(12);
        if (bg->getLocation() >= 0) bg->resetLocation();


        //Move the car
//        for(std::list<Car*>::iterator it = cars.begin(); it != cars.end(); it++)
//        {
//
//        }
        player->updateLocation();
        c->updateLocation();

        if (c->getYPos() >= 640) {
            c->setYPos(-250);
            c->setYVelocity(cSpeed++);
        }


        /**
         * Collision detection
         */
        if (player->isColliding(c))
        {
            isPlaying = false;
            factory->quit();
        }

        /**
         * Visualize
         */
        factory->startRendering();

        bg->visualize();
        player->visualize();
        c->visualize();

        score->render();
        lives->render();

        factory->finishRendering();

        //17 corresponds to 60 fps
        while (chron->getTimePassed() < 17) {}
    }
}

Game::~Game() {

}
