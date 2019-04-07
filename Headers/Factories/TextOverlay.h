//
// Created by Dieter on 25/03/2019.
//

#ifndef UNTITLED_TEXTOVERLAY_H
#define UNTITLED_TEXTOVERLAY_H


#include <string>

class TextOverlay {
public:
    TextOverlay();
    ~TextOverlay();

    virtual void setPosition(int x, int y) = 0;
    virtual void setText(std::string) = 0;
    virtual int getTextWidth() = 0;
    virtual void render() = 0;
};


#endif //UNTITLED_TEXTOVERLAY_H
