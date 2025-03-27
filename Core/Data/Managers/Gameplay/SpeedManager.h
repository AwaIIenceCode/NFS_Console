// Created by AwallencePC on 26.03.2025.
//

#ifndef SPEEDMANAGER_H
#define SPEEDMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../../Config/Utils/Logger.h"

class SpeedManager {
public:
    SpeedManager(float initialSpeed, float baseSpeed, float accelerationTime);
    void update(float deltaTime);
    void resetAcceleration();
    float getCurrentSpeed() const { return currentSpeed; }
    void setCurrentSpeed(float newSpeed); // Добавляем метод для установки скорости

private:
    float initialSpeed;
    float baseSpeed;
    float accelerationTime;
    float currentSpeed;
    sf::Clock accelerationTimer;
};

#endif //SPEEDMANAGER_H