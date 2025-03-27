// Created by AwallencePC on 27.03.2025.
//

#include "Timer.h"

Timer::Timer() : started(false) {}

void Timer::start() {
    started = true;
    clock.restart();
}

float Timer::getElapsedTime() const {
    return clock.getElapsedTime().asSeconds();
}