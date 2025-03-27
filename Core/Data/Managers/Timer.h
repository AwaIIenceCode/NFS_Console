// Created by AwallencePC on 27.03.2025.
//

#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>
#include "../../Config/Utils/Logger.h"

class Timer {
public:
    Timer();
    void start();
    float getElapsedTime() const;
    bool isStarted() const { return started; }

private:
    sf::Clock clock;
    bool started;
};

#endif //TIMER_H