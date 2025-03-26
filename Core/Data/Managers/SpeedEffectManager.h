// Created by AwallencePC on 26.03.2025.
//

#ifndef SPEEDEFFECTMANAGER_H
#define SPEEDEFFECTMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../Config/Utils/Logger.h"

class SpeedEffectManager {
public:
    SpeedEffectManager(float initialSpeed); // Добавляем параметр
    void update(float deltaTime, float& currentSpeed, float baseSpeed);
    void applyBoost(float& currentSpeed);
    void applySlowdown(float& currentSpeed);

private:
    bool isBoosted;
    bool isSlowed;
    float effectDuration;
    float effectTimer;
    float boostMultiplier;
    float slowdownMultiplier;
    float initialSpeed; // Добавляем начальную скорость
};

#endif //SPEEDEFFECTMANAGER_H