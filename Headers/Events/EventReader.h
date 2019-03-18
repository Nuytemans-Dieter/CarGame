//
// Created by Dieter on 18/03/2019.
//

#ifndef UNTITLED_ABSTRACTWINDOWCLOSER_H
#define UNTITLED_ABSTRACTWINDOWCLOSER_H


class EventReader {
public:
    enum event {
        WINDOW_CLOSE,
        ESC,
        ARROW_LEFT,
        ARROW_RIGHT,
        SPACEBAR,
        NONE
    };

    EventReader();
    ~EventReader();

    virtual event getCurrentEvent() = 0;

};


#endif //UNTITLED_ABSTRACTWINDOWCLOSER_H
