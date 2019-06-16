
#include <iostream>
#include "Headers/Factories/Text/TextFactory.h"
#include "Headers/Factories/AbstractFactory.h"
#include "Headers/Game.h"
#include "Headers/Factories/SDL/SDLFactory.h"
#include "Headers/Events/SDL/SDLEventReader.h"

using namespace std;

int main( int argc, char *argv[] )
{
    AbstractFactory* aFact = new SDLFactory();
    AbstractEventReader* aEvent = new SDLEventReader();
    Game *game = game->getInstance(aFact, aEvent);


    return 0;
}