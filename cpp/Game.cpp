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
#include "../Headers/Sound/Sound.h"

Game::Game(AbstractFactory *aFact, AbstractEventReader *aEvent) {
    factory = aFact;
    eventReader = aEvent;
    gameLoop();
}

int numCars;

void Game::gameLoop() {
    //Initiaize general variables
    bool isPlaying = true;
    bool pause = false;
    int points = 1;
    int difficulty = 0;

    /**
     * Game settings
     */
    //Player settings
    const int playerVelocity = 5;                   //The velocity of the player (equal in all directions)
    const int laserVelocity = -7;                   //The velocity of the projectiles shot by the player
    int playerLives = 3;                            //The amount of lives a player starts with
    const int maxLasers = 10;                       //The maximum amount of lasers
    int playerLasers = maxLasers;                   //The starting amount of lasers

    //Difficulty settings
    const int maxCars = 12;                         //Maximum amount of randomly spawned enemy cars
    const int difficultyIncrement = 5;              //How hard the difficulty will rise upon each car spawn
    const int maxDifficulty = 100;                  //The point at which the difficulty maxes out
    const int difficultyFactor = 5000;              //The amount of points the player should earn before difficulty is increased
    int carSpawnVelocity = 2;                       //This is the starting value, it will increase during gameplay
    const int spawnChance = 150;                    //Not in %, but the inverse percentage. The actual chance of spawning is 1/spawnChange
    const int incrSpeed = 2;                        //The speed that is added to enemy cars at every set interval
    const int speedupPoints = 5000;                 //The amount of point a player needs for each speedup
    const int shootChance = 2;                      //The chance (in %) that cars shoot a laser downward
    const int enemyLaserSpeedOffset = 2;            //The amount of speed the laser is higher than the car it spawned

    //Timing settings
    const double millisecondsPerFrame = 16.7;       //16.7 corresponds roughly to 60 fps
    const int fpsRefreshRate = 1000;                //After how many milliseconds the fps counter should update
    const int invincibleTime = 2000;                //The time in milliseconds that the player is invincible after being hit
    const int shootDelay = 500;                     //The minumum time between two shots
    const int textDuration = 2000;                  //The time (ms) in which a pop-up text will be visible
    const int minPauseTime = 500;                   //The minimum amount of pause (and play) time there should be before pause/play is allowed
    const int laserSpawnDelay = 100;                //The minimum delay between two laser spawns

    //Back-end settings
    const int spawnLanes[4] = {108, 218, 333, 443}; //Location (X) of each lane
    const int numCarColors = 6;                     //MUST be equal to the size of the Car::Color enum!
    const int numSongs = 10;                        //MUST be equal to the size of the Sound::music enum!
    const int maxEnemyLasers = 20;                  //The max possible amount of concurrent enemy lasers
    const int screenHeight = 640;                   //The height of the screen
    const int screenWidth = 640;                    //The width of the screen

    //visual settings
    int backgroundMoveDownSpeed = 6;                //The speed at which the background moves down each frame

    //Initialize chronos & start timing if needed
    Chrono* chron = new Chrono();
    Chrono* fpsRefresh = new Chrono(fpsRefreshRate);
    Chrono* hitTimer = new Chrono();
    Chrono* shootTimer = new Chrono();
    Chrono* textTimer = new Chrono();
    Chrono* pauseTimer = new Chrono();
    Chrono* laserTimer = new Chrono();

    fpsRefresh->startTime();
    hitTimer->startTime();
    shootTimer->startTime();
    pauseTimer->startTime();
    laserTimer->startTime();

    srand(time(NULL));

    //Initialize the lists
    Car* cars [maxCars] = {0};
    Laser* lasers [maxLasers] = {0};
    Laser* enemyLasers [maxEnemyLasers] = {0};

    numCars = 0;
    int numLasers = 0;

    //Create score overlay
    TextOverlay* score = factory->createTextOverlay();
    score->setPosition(1,510);

    //Create lives overlay
    TextOverlay* lives = factory->createTextOverlay();
    lives->setPosition(1,550);

    //Create fps overlay
    TextOverlay* fps = factory->createTextOverlay(15);
    fps->setPosition(1,10);

    //Create ammo overlay
    TextOverlay* ammo = factory->createTextOverlay();
    ammo->setPosition(1,590);

    //Create message overlay
    TextOverlay* text = factory->createTextOverlay();
    //Forumula to center text at x-position: screenWidth/2 - text->getTextWidth()/2 (after setting text)


    //Create background
    //1233 = top pixel of perfect reset
    Background* bg = factory->createBackground();
    bg->setResetLocation(-594);
    bg->resetLocation();

    //Create player
    Car* player = factory->createCar(Car::RED);
    player->setXPos(95); player->setYPos(400);
    player->setBoundaries(83,250,562,635);

    /**
     * Load sounds and music
     */
    Sound* music = factory->createSound();
    music->loadMusic(Sound::music(rand() % numSongs));

    Sound* laser = factory->createSound();
    laser->loadSound(Sound::shoot);

    Sound* explosion = factory->createSound();
    explosion->loadSound(Sound::explosion);

    Sound* invincible = factory->createSound();
    invincible->loadSound(Sound::invincible);

    Sound* speedup = factory->createSound();
    speedup->loadSound(Sound::speedup);

    //Start a music loop
    music->playMusicLoop();

    while (isPlaying)
    {
        //Start time measurement at the start time of each frame
        chron->startTime();

        /**
         * Difficulty & speedup management
         */
        if (difficulty != maxDifficulty && points % difficultyFactor == 1) difficulty += difficultyIncrement;
        if (points % speedupPoints == 0) {
            carSpawnVelocity += incrSpeed;
            backgroundMoveDownSpeed += incrSpeed;
            for (int i = 0; i < maxCars; i++)
            {
                if (cars[i] != 0)
                {
                    cars[i]->setYVelocity(carSpawnVelocity);
                }
            }

            text->setText("You are speeding up!");
            text->setPosition(screenWidth/2 - text->getTextWidth()/2, 230);
            textTimer->startTime();

            playerLasers = maxLasers;
            speedup->playSound();
        }

        /**
         * Random car generator
         */
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

        /**
         * Read input->Movement of player
         */
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

        /*
         * Read input->other buttons of player (and loop while paused)
         */
        do {
            switch (eventReader->getCurrentEvent()) {
                case AbstractEventReader::WINDOW_CLOSE:
                    factory->quit();
                    pause = false;
                    isPlaying = false;
                    break;
                case AbstractEventReader::ESC:
                    if (pauseTimer->getTimePassed() > minPauseTime){
                        pauseTimer->startTime();
                        pause = !pause;
                    }
                    break;
                case AbstractEventReader::SPACEBAR:
                    if (shootTimer->getTimePassed() >= shootDelay && numLasers < maxLasers && playerLasers != 0) {
                        int firstFree = 0;
                        for (int i = 0; i < maxLasers; i++) {
                            if (lasers[i] == 0) {
                                firstFree = i;
                                i = maxLasers;
                            }
                        }
                        lasers[firstFree] = factory->createLaser();
                        lasers[firstFree]->setYVelocity(laserVelocity);
                        lasers[firstFree]->setYPos(player->getYPos());
                        lasers[firstFree]->setXPos(player->getXPos() + player->getWidth() / 2);
                        numLasers++;
                        playerLasers--;
                        shootTimer->startTime();

                        laser->playSound();
                    }
                    break;
                case AbstractEventReader::CHEAT_SPEEDUP:
                    if (textTimer->getTimePassed() > textDuration) {
                        points += speedupPoints - (points % speedupPoints) - 1;
                        difficulty = ((points - points % difficultyFactor) / difficultyFactor) * difficultyIncrement +
                                     difficultyIncrement;
                        if (difficulty > maxDifficulty) difficulty = maxDifficulty;

                        text->setText("You used a cheatcode! Speeding up...");
                        text->setPosition(screenWidth / 2 - text->getTextWidth() / 2, 230);

                        textTimer->startTime();
                    }
                    break;
                case AbstractEventReader::NONE:
                    break;
            }
        } while(pause);

        /**
         * Background movement
         */
        bg->moveDown(backgroundMoveDownSpeed);
        if (bg->getLocation() >= 0) bg->resetLocation();

        /**
         * Move objects, perform collision detection & render enemy cars
         * Also allow cars to shoot
         */
        factory->startRendering(); //Perform tasks to start rendering
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

        for (int i = 0; i < maxEnemyLasers; i++)
        {
            if (enemyLasers[i] != 0)
            {
                enemyLasers[i]->updateLocation();
                enemyLasers[i]->visualize();
                if (enemyLasers[i]->getYPos() + enemyLasers[i]->getHeight() < 0)
                {
                    delete enemyLasers[i]; enemyLasers[i] = 0;
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
                    //Randomly allow an enemy car to shoot
                    if (rand() % 100 < shootChance)
                    {
                        for (int j = 0; j < maxEnemyLasers; j++)
                        {
                            if (enemyLasers[j] == 0)
                            {
                                if (laserTimer->getTimePassed() > laserSpawnDelay) {

                                    enemyLasers[j] = factory->createLaser();
                                    enemyLasers[j]->setYPos(cars[i]->getYPos() + cars[i]->getHeight() - enemyLasers[j]->getHeight());
                                    enemyLasers[j]->setXPos(cars[i]->getXPos() + cars[i]->getWidth() / 2 - enemyLasers[j]->getWidth() / 2);
                                    enemyLasers[j]->setYVelocity(carSpawnVelocity + enemyLaserSpeedOffset);
                                    enemyLasers[j]->updateLocation();
                                    enemyLasers[j]->visualize();

                                    laserTimer->startTime();
                                }
                            }
                        }
                    }
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

                            text->setText("You hit a car! You are temporarily invincible!");
                            text->setPosition(screenWidth/2 - text->getTextWidth()/2, 230);
                            textTimer->startTime();

                            invincible->playSound();

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

                                explosion->playSound();

                                j = maxLasers;
                            }
                        }

                        if (cars[i] != 0)
                        {
                            for (int j = 0; j < maxEnemyLasers; j++)
                            {
                                if (enemyLasers[j] != 0 && cars[i]->isColliding(enemyLasers[j]))
                                {
                                    if (cars[i]->getYPos() > enemyLasers[j]->getYPos()) {
                                        std::cout << "Laser collide" << std::endl;
                                        delete cars[i];
                                        cars[i] = 0;
                                        numCars--;

                                        delete enemyLasers[j];
                                        enemyLasers[j] = 0;

                                        explosion->playSound();

                                        j = maxEnemyLasers;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //Update player & text
        player->updateLocation();
        score->setText("Score: " + std::to_string((points-points%10)/10));
        lives->setText("Lives: " + std::to_string(playerLives));
        ammo->setText("Ammo: " + std::to_string(playerLasers) + " / " + std::to_string(maxLasers));

        /**
         * Visualize
         */
        player->visualize();
        score->render();
        lives->render();
        ammo->render();
        if (textTimer->getTimePassed() < textDuration)
        {
            text->render();
        }

        while (chron->getTimePassed() < millisecondsPerFrame) {}
        if (fpsRefresh->getTimePassed() >= fpsRefreshRate) {
            fps->setText("fps: " + std::to_string( (int) round(1000 / chron->getTimePassed()) ));
            fpsRefresh->startTime();
        }
        fps->render();
        factory->finishRendering();

        //Add to score
        points++;
    }
}

Game::~Game() {

}
