//
// Created by Dieter on 18/03/2019.
//

#ifndef UNTITLED_ABSTRACTWINDOWCLOSER_H
#define UNTITLED_ABSTRACTWINDOWCLOSER_H


class AbstractEventReader {
public:
    enum event {
        WINDOW_CLOSE,
        ARROW_LEFT,
        ARROW_UP,
        ARROW_RIGHT,
        ARROW_DOWN,
        SPACEBAR,
        ESC,
        NONE
    };

    AbstractEventReader();
    ~AbstractEventReader();

    virtual event getCurrentEvent() = 0;

};


#endif //UNTITLED_ABSTRACTWINDOWCLOSER_H
