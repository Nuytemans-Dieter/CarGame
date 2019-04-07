//
// Created by Dieter on 6/04/2019.
//

#include "../Headers/Chrono.h"

Chrono::Chrono() {
    currentFrame = std::chrono::system_clock::now();
    lastFrame = std::chrono::system_clock::now();
}

Chrono::Chrono(double delta)
{
    firstDelta = delta;
}

Chrono::~Chrono() {

}

void Chrono::startTime()
{
    lastFrame = std::chrono::system_clock::now();
}

double Chrono::getTimePassed()
{
    currentFrame = std::chrono::system_clock::now();
    if (firstDelta == 0){
        std::chrono::duration<double, std::milli> delta = currentFrame - lastFrame;
        return delta.count();
    } else return firstDelta;
}
