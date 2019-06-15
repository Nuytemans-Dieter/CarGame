//
// Created by Dieter on 18/03/2019.
//

#ifndef UNTITLED_SDLEVENTREADER_H
#define UNTITLED_SDLEVENTREADER_H


#include "../AbstractEventReader.h"

class SDLEventReader : public AbstractEventReader {

public:
    SDLEventReader();
    ~SDLEventReader();

    // Get an AbstractEventReader::event by reading the keyboard.
    AbstractEventReader::event getCurrentEvent();
    // Get in which direction the arrow keys are being pressed.
    AbstractEventReader::movement getMovement() ;

};


#endif //UNTITLED_SDLEVENTREADER_H
