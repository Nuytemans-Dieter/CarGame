Generic CarGame
=====
#### A simple 2D racing game, written in C++
This project is an assignment for an advanced programming course.
The goal of the game is to get as many points as possible by avoiding to hit obstacles.

# Game logic library
- Separation between game logic and game presentation
- Hierchy of game entities and their interactions
# Specifications
- Use the singleton design pattern to represent the game
- The game object may not contain any calls to visualization libraries or input libraries
- The abstract factory pattern must be used to create entities in the game object
- The game contains a way to time events
- Enemy cars drive on different lanes but slower than the players. They, and the player, can shoot projectiles. Powerups lay on the road and have an effect on the game/player. Enemy cars can be destroyed by hitting them with a projectile.
# Visual & interactive implementation
- Use the SDL2 library
