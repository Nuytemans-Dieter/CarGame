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

    // Set the position of the text.
    virtual void setPosition(int x, int y) = 0;
    // Set the text to a given string.
    virtual void setText(std::string) = 0;
    // Get the width of the text.
    virtual int getTextWidth() = 0;
    // Render the text on screen.
    virtual void render() = 0;
};


#endif //UNTITLED_TEXTOVERLAY_H
