//
// Created by Dieter on 18/03/2019.
//

#ifndef UNTITLED_ABSTRACTWINDOWCLOSER_H
#define UNTITLED_ABSTRACTWINDOWCLOSER_H


class AbstractEventReader {
public:
    enum event {
        WINDOW_CLOSE,
        SPACEBAR,
        ESC,
        CHEAT_SPEEDUP,
        NONE
    };

    enum movement {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        UPRIGHT,
        UPLEFT,
        DOWNLEFT,
        DOWNRIGHT,
        STOP
    };

    AbstractEventReader();
    ~AbstractEventReader();

    // Get an AbstractEventReader::event by reading the keyboard.
    virtual event getCurrentEvent() = 0;
    // Get in which direction the arrow keys are being pressed.
    virtual movement getMovement() = 0;

};


#endif //UNTITLED_ABSTRACTWINDOWCLOSER_H
