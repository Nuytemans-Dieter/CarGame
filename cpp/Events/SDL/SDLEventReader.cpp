//
// Created by Dieter on 18/03/2019.
//

#include <SDL2/SDL_events.h>
#include <iostream>
#include <SDL2/SDL_timer.h>
#include "../../../Headers/Events/SDL/SDLEventReader.h"

SDLEventReader::SDLEventReader() {}

SDLEventReader::~SDLEventReader() {}

AbstractEventReader::event SDLEventReader::getCurrentEvent() {
    SDL_Event e;

    if (SDL_PollEvent( &e ) != 0)
    {
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE])
            return ESC;
    }


    int i = 0;
    while (SDL_PollEvent( &e ) != 0 || i < 10)
    {
        i++;

        if (e.type == SDL_QUIT)
        {
            return WINDOW_CLOSE;
        } else
        {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[ SDL_SCANCODE_RIGHT ] && !state[ SDL_SCANCODE_LEFT ])
                return ARROW_RIGHT;
            else if (state[ SDL_SCANCODE_LEFT ] && !state[ SDL_SCANCODE_RIGHT ])
                return ARROW_LEFT;
            else if (state[ SDL_SCANCODE_UP ] && !state[ SDL_SCANCODE_DOWN ])
                return ARROW_UP;
            else if (state[ SDL_SCANCODE_DOWN ] && !state [ SDL_SCANCODE_UP ])
                return ARROW_DOWN;
            else if (state[ SDL_SCANCODE_SPACE ])
                return SPACEBAR;
        }
    }
    return NONE;
}