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
    //Initiaize general variables
    bool isPlaying = true;
    int playerVelocity = 5;
    int points = 0;
    int difficulty = 0;

    //Instantiate chrono
    Chrono* chron = new Chrono();
    srand(time(NULL));

    //Initialize the enemy car's list
    Car* cars [9] = {0};
    int numCars = 0;

    //Create score overlay
    TextOverlay* score = factory->createTextOverlay();
    score->setPosition(1,10);

    //Create lives overlay
    TextOverlay* lives = factory->createTextOverlay();
    lives->setPosition(565,10);
    lives->setText("Lives: 3");

    TextOverlay* diff = factory->createTextOverlay();
    diff->setPosition(1,50);
    diff->setText("Difficulty");

    //Create background
    Background* bg = factory->createBackground();
    bg->setResetLocation(-592);
    bg->resetLocation();

    //Create player
    Car* player = factory->createCar(Car::RED);
    player->setXPos(95); player->setYPos(400);
    player->setBoundaries(80,250,560,640);

    while (isPlaying)
    {
        //Start time measurement at the start time of each frame
        chron->startTime();

        //Calculate score
        score->setText("Score: " + std::to_string(points));
        diff->setText("Diff: " + std::to_string(difficulty));
        points++;

        //Random car generator
        if (rand() % (200 - difficulty) == 0 && numCars < 9)
        {
            if (difficulty < 150) difficulty += 2;
            //Find the first available place in the enemy car list
            int firstFreeSpot;
            for (int i = 0; i < 9; i++)
            {
                if (cars[i] == 0)
                {
                    firstFreeSpot = i;
                    i = 9;
                }
            }

            //Pick a random car color
            Car::Color randomColor = Car::Color(rand() % 6);
            //Create a car at a random location with a random velocity
            cars[firstFreeSpot] = factory->createCar(randomColor);
            //x-locations of lanes: 440 330 215 110
            cars[firstFreeSpot]->setXPos(((rand() % 4)+1)*110-5); cars[firstFreeSpot]->setYPos(-250);
            cars[firstFreeSpot]->setYVelocity(3);

            //Find a non-colliding spot to spawn the car
            bool isColliding;
            do {
                isColliding = false;
                for (int i = 0; i < 9; i++) {
                    if (i != firstFreeSpot && cars[i] != 0) {
                        if (cars[firstFreeSpot]->isColliding(cars[i]))
                        {
                            cars[firstFreeSpot]->setYPos(cars[firstFreeSpot]->getYPos() - cars[i]->getHeight());
                            isColliding = true;
                            i = 9;
                        }
                    }
                }
            } while (isColliding);

            numCars++;
        }

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
        }

        //Handle background
        bg->moveDown(12);
        if (bg->getLocation() >= 0) bg->resetLocation();

        /**
         * Move objects & render enemy cars
         */
        factory->startRendering();
        bg->visualize();
        for (int i = 0; i < 9; i++)
        {
            if (cars[i] != 0)
            {
                if (cars[i]->getYPos() > 640)
                {
                    delete cars[i];
                    cars[i] = 0;
                    numCars--;
                } else {
                    cars[i]->updateLocation();
                    cars[i]->visualize();

                    /**
                     * Collision detection
                     */
                     //Check collision with player
                    if (cars[i]->isColliding(player)) {
                        isPlaying = false;
                        factory->quit();
                    }

                }
            }
        }

        player->updateLocation();

        /**
         * Visualize
         */
        player->visualize();
        score->render();
        lives->render();
        diff->render();
        factory->finishRendering();

        //17 corresponds to 60 fps
        while (chron->getTimePassed() < 17) {}
    }
}

Game::~Game() {

}
