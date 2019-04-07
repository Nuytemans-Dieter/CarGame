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

    AbstractEventReader::event getCurrentEvent();
    AbstractEventReader::movement getMovement() ;

};


#endif //UNTITLED_SDLEVENTREADER_H
