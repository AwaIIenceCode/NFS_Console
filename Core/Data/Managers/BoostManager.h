//
// Created by AwallencePC on 26.03.2025.
//

#ifndef BOOSTMANAGER_H
#define BOOSTMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../Config/Utils/Logger.h"

class BoostManager
{
public:
    BoostManager();
    void update(float deltaTime, float& currentSpeed, float baseSpeed);
    void applyBoost(float& currentSpeed);

private:
    bool isBoosted;
    float boostDuration;
    float boostTimer;
    float boostMultiplier;
};

#endif //BOOSTMANAGER_H
