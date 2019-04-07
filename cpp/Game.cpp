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
#include "../Headers/GameObjects/Laser.h"

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

int numCars;

void Game::gameLoop() {
    //Initiaize general variables
    bool isPlaying = true;
    int points = 0;
    int difficulty = 0;

    /**
     * Game settings
     */
    //Player settings
    const int playerVelocity = 5;                   //The velocity of the player (equal in all directions)
    const int laserVelocity = -7;                   //The velocity of the projectiles shot by the player
    int playerLives = 3;                            // The amount of lives a player starts with
    const int maxLasers = 5;                        //The maximum amount of lasers
    int playerLasers = maxLasers;                   //The starting amount of lasers

    //Difficulty settings
    const int maxCars = 12;                         //Maximum amount of randomly spawned enemy cars
    const int difficultyIncrement = 10;             //How hard the difficulty will rise upon each car spawn
    const int maxDifficulty = 150;                  //The point at which the difficulty maxes out
    int carSpawnVelocity = 2;                       //This is the starting value, it will increase during gameplay
    const int spawnChance = 200;                    //Not in %, but the inverse percentage. The actual chance of spawning is 1/spawnChange
    const int incrSpeed = 2;                        //The speed that is added to enemy cars at every set interval

    //Back-end settings
    const int spawnLanes[4] = {108, 218, 333, 443}; //Location (X) of each lane
    const int numCarColors = 6;                     //Must be equal to the size of the Car::Color enum!
    int backgroundMoveDownSpeed = 12;               //The speed at which the background moves down each frame
    const int screenHeight = 640;                   //The height of the screen


    //Timing settings
    const double millisecondsPerFrame = 16.7;       //16.7 corresponds roughly to 60 fps
    const int fpsRefreshRate = 1000;                //After how many milliseconds the fps counter should update
    const int invincibleTime = 2000;                //The time in milliseconds that the player is invincible after being hit
    const int shootDelay = 500;                     //The minumum time between two shots


    //Initialize chronos & start timing if needed
    Chrono* chron = new Chrono();
    Chrono* fpsRefresh = new Chrono(fpsRefreshRate);
    Chrono* hitTimer = new Chrono();
    Chrono* shootTimer = new Chrono();

    fpsRefresh->startTime();
    hitTimer->startTime();
    shootTimer->startTime();

    srand(time(NULL));

    //Initialize the lists
    Car* cars [maxCars] = {0};
    Laser* lasers [maxLasers] = {0};

    numCars = 0;
    int numLasers = 0;

    //Create score overlay
    TextOverlay* score = factory->createTextOverlay();
    score->setPosition(1,10);

    TextOverlay* diff = factory->createTextOverlay();
    diff->setPosition(1,50);

    //Create lives overlay
    TextOverlay* lives = factory->createTextOverlay();
    lives->setPosition(565,10);

    //Create fps overlay
    TextOverlay* fps = factory->createTextOverlay();
    fps->setPosition(565,50);

    //Create ammo overlay
    TextOverlay* ammo = factory->createTextOverlay();
    ammo->setPosition(1,90);

    //Create background
    //1233
    Background* bg = factory->createBackground();
    bg->setResetLocation(-594);
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
        points++;
        if (difficulty != maxDifficulty && points%1000 == 0) difficulty += difficultyIncrement;
        if (points%5000 == 0) {
            carSpawnVelocity += incrSpeed;
            backgroundMoveDownSpeed += incrSpeed;
            for (int i = 0; i < maxCars; i++)
            {
                if (cars[i] != 0)
                {
                    cars[i]->setYVelocity(carSpawnVelocity);
                }
            }
        }

        //Random car generator
        if (numCars < maxCars && rand() % (spawnChance - difficulty) == 0)
        {
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
            cars[firstFreeSpot]->setYVelocity(carSpawnVelocity);

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

        //Read input->Movement of player
        switch(eventReader->getMovement())
        {
            case AbstractEventReader::LEFT:
                player->setXVelocity(-playerVelocity);      break;
            case AbstractEventReader::RIGHT:
                player->setXVelocity(playerVelocity);       break;
            case AbstractEventReader::UP:
                player->setYVelocity( -playerVelocity );    break;
            case AbstractEventReader::DOWN:
                player->setYVelocity( playerVelocity );     break;
            case AbstractEventReader::UPRIGHT:
                player->setXVelocity( playerVelocity );
                player->setYVelocity( - playerVelocity );   break;
            case AbstractEventReader::UPLEFT:
                player->setXVelocity( - playerVelocity );
                player->setYVelocity( - playerVelocity );   break;
            case AbstractEventReader::DOWNRIGHT:
                player->setXVelocity( playerVelocity );
                player->setYVelocity( playerVelocity );     break;
            case AbstractEventReader::DOWNLEFT:
                player->setXVelocity( - playerVelocity );
                player->setYVelocity( playerVelocity );     break;
            case AbstractEventReader::STOP:
                player->setXVelocity(0);
                player->setYVelocity(0);                    break;
        }

        //Read input: other buttons of player
        switch (eventReader->getCurrentEvent()) {
            case AbstractEventReader::WINDOW_CLOSE:
                factory->quit();
                isPlaying = false;
                break;
            case AbstractEventReader::ESC:
                //DO something
                break;
            case AbstractEventReader::SPACEBAR:
                if(shootTimer->getTimePassed() >= shootDelay && numLasers < maxLasers && playerLasers != 0)
                {
                    int firstFree = 0;
                    for (int i = 0; i < maxLasers; i++)
                    {
                        if (lasers[i] == 0)
                        {
                            firstFree = i;
                            i = maxLasers;
                        }
                    }
                    lasers[firstFree] = factory->createLaser();
                    lasers[firstFree]->setYVelocity(laserVelocity);
                    lasers[firstFree]->setYPos(player->getYPos());
                    lasers[firstFree]->setXPos(player->getXPos() + player->getWidth()/2);
                    numLasers++; playerLasers--;
                    shootTimer->startTime();
                }
                break;
            case AbstractEventReader::NONE:
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

        for (int i = 0; i < maxLasers; i++)
        {
            if (lasers[i] != 0)
            {
                lasers[i]->updateLocation();
                lasers[i]->visualize();
                if (lasers[i]->getYPos() + lasers[i]->getHeight() < 0)
                {
                    delete lasers[i];lasers[i] = 0;
                    numLasers--;
                }
            }
        }

        for (int i = 0; i < maxCars; i++)
        {
            if (cars[i] != 0)
            {
                cars[i]->updateLocation();
                if (cars[i]->getYPos() > screenHeight)
                {
                    delete cars[i]; cars[i] = 0;
                    numCars--;
                } else {
                    cars[i]->visualize();

                    /**
                     * Collision detection
                     */
                     //Check collision with player
                    if (cars[i]->isColliding(player)) {
                        delete cars[i]; cars[i] = 0;
                        numCars--;
                        if (hitTimer->getTimePassed() > invincibleTime)
                        {
                            hitTimer->startTime();
                            playerLives--;
                            if (playerLives < 0)
                            {
                                isPlaying = false;
                                factory->quit();
                            }
                        }
                    } else {
                        //Check collision with projectiles
                        for (int j = 0; j < maxLasers; j++) {
                            if (lasers[j] != 0 && cars[i]->isColliding(lasers[j])) {
                                delete cars[i];
                                cars[i] = 0;
                                numCars--;

                                delete lasers[j];
                                lasers[j] = 0;
                                numLasers--;

                                playerLasers+=2;
                                if (playerLasers > maxLasers) playerLasers = maxLasers;

                                j = maxLasers;
                            }
                        }
                    }
                }
            }
        }

        //Update player & text
        player->updateLocation();
        score->setText("Score: " + std::to_string(points));
        diff->setText("Difficulty: " + std::to_string(difficulty));
        lives->setText("Lives: " + std::to_string(playerLives));
        ammo->setText("Ammo: " + std::to_string(playerLasers) + " / " + std::to_string(maxLasers));

        /**
         * Visualize
         */
        player->visualize();
        score->render();
        lives->render();
        diff->render();
        ammo->render();


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
