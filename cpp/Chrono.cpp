//
// Created by Dieter on 6/04/2019.
//

#include "../Headers/Chrono.h"

Chrono::Chrono() {
    currentFrame = std::chrono::system_clock::now();
    lastFrame = std::chrono::system_clock::now();
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
    std::chrono::duration<double, std::milli> delta = currentFrame - lastFrame;
    return delta.count();
}
