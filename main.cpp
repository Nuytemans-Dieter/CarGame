
#include <iostream>
#include "Headers/Factories/Text/TextFactory.h"
#include "Headers/Factories/AbstractFactory.h"
#include "Headers/Game.h"
#include "Headers/Factories/SDL/SDLFactory.h"

using namespace std;

int main( int argc, char *argv[] )
{
    AbstractFactory* aFact = new SDLFactory();
    Game *game = new Game(aFact);
    game->start();


    return 0;
}