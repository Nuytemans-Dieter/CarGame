//
// Created by Dieter on 18/03/2019.
//

#ifndef UNTITLED_BACKGROUND_H
#define UNTITLED_BACKGROUND_H


class Background {
public:
    Background();
    ~Background();

    virtual void visualize() = 0;

    // Gets the current Y-position of this background.
    int getLocation();
    // Move down x pixels.
    void moveDown(int x);
    // Reset the background to the default location.
    void resetLocation();

    // Choose the Y-coordinate to which the background should reset.
    void setResetLocation(int);

private:
    int location;
    int resetLocationY;
};


#endif //UNTITLED_BACKGROUND_H
