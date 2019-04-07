//
// Created by Dieter on 6/04/2019.
//

#ifndef UNTITLED_CHRONO_H
#define UNTITLED_CHRONO_H


#include <chrono>

class Chrono {
public:
    //Create a Chrono
    Chrono();
    //Create a Chrono that will return the given double when Chrono::getTimePassed() is called for the first time
    Chrono(double);
    ~Chrono();
    void startTime();
    //Get the amount of time that has been passed since this function was last called
    double getTimePassed();

private:
    std::chrono::system_clock::time_point currentFrame;
    std::chrono::system_clock::time_point lastFrame;
    double firstDelta = 0;
};


#endif //UNTITLED_CHRONO_H
