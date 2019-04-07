//
// Created by Dieter on 4/03/2019.
//

#include <iostream>
#include <list>
#include <cmath>
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
    int points = 0;
    int difficulty = 0;
    //Game settings
    const int playerVelocity = 5;
    const int maxCars = 9;
    const int difficultyIncrement = 2;
    const int maxDifficulty = 150;
    const int spawnChance = 200; //Not in %, but the inverse percentage. The actual chance of spawning is 1/spawnChange
    const int spawnLanes[4] = {108, 218, 333, 443};
    const int numCarColors = 6; //Must be equal to the size of the Car::Color enum!
    const int backgroundMoveDownSpeed = 12;
    const int screenHeight = 640;
    const double millisecondsPerFrame = 16.7; //17 corresponds to 60 fps
    const int fpsRefreshRate = 1000;

    //Instantiate chrono
    Chrono* chron = new Chrono();
    Chrono* fpsRefresh = new Chrono();
    fpsRefresh->startTime();
    srand(time(NULL));

    //Initialize the enemy car's list
    Car* cars [maxCars] = {0};
    int numCars = 0;

    //Create score overlay
    TextOverlay* score = factory->createTextOverlay();
    score->setPosition(1,10);

    TextOverlay* diff = factory->createTextOverlay();
    diff->setPosition(1,50);
    diff->setText("Difficulty: 0");

    //Create lives overlay
    TextOverlay* lives = factory->createTextOverlay();
    lives->setPosition(565,10);
    lives->setText("lives: 3");

    //Create lives overlay
    TextOverlay* fps = factory->createTextOverlay();
    fps->setPosition(565,50);
    fps->setText("fps: 60");

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
        diff->setText("Difficulty: " + std::to_string(difficulty));
        points++;

        //Random car generator
        if (rand() % (spawnChance - difficulty) == 0 && numCars < maxCars)
        {
            if (difficulty < maxDifficulty) difficulty += difficultyIncrement;
            //Find the first available place in the enemy car list
            int firstFreeSpot;
            for (int i = 0; i < maxCars; i++)
            {
                if (cars[i] == 0)
                {
                    firstFreeSpot = i;
                    i = maxCars;
                }
            }

            //Pick a random car color
            Car::Color randomColor = Car::Color(rand() % numCarColors);
            //Create a car at a random location with a random velocity
            cars[firstFreeSpot] = factory->createCar(randomColor);
            //x-locations of lanes: 440 330 215 110
            cars[firstFreeSpot]->setXPos(spawnLanes[rand() % 4]); cars[firstFreeSpot]->setYPos(-250);
            cars[firstFreeSpot]->setYVelocity(3);

            //Find a non-colliding spot to spawn the car
            bool isColliding;
            do {
                isColliding = false;
                for (int i = 0; i < maxCars; i++) {
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
        bg->moveDown(backgroundMoveDownSpeed);
        if (bg->getLocation() >= 0) bg->resetLocation();

        /**
         * Move objects, perform collision detection & render enemy cars
         */
        factory->startRendering();
        bg->visualize();
        for (int i = 0; i < maxCars; i++)
        {
            if (cars[i] != 0)
            {
                if (cars[i]->getYPos() > screenHeight)
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


        while (chron->getTimePassed() < millisecondsPerFrame) {}
        if (fpsRefresh->getTimePassed() >= fpsRefreshRate) {
            fps->setText("fps: " + std::to_string( (int) round(1000 / chron->getTimePassed()) ));
            fpsRefresh->startTime();
        }
        fps->render();
        factory->finishRendering();
    }
}

Game::~Game() {

}
