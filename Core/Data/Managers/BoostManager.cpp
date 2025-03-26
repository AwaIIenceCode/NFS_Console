//
// Created by AwallencePC on 26.03.2025.
//

#include "BoostManager.h"

BoostManager::BoostManager()
    : isBoosted(false), boostDuration(3.0f), boostTimer(0.0f), boostMultiplier(1.5f) {}

void BoostManager::update(float deltaTime, float& currentSpeed, float baseSpeed)
{
    if (isBoosted)
    {
        boostTimer += deltaTime;

        if (boostTimer >= boostDuration)
        {
            isBoosted = false;
            currentSpeed = baseSpeed;
            Logger::getInstance().log("Boost ended. Speed returned to " + std::to_string(currentSpeed));
        }
    }
}

void BoostManager::applyBoost(float& currentSpeed)
{
    isBoosted = true;
    boostTimer = 0.0f;
    currentSpeed *= boostMultiplier;
    Logger::getInstance().log("Boost applied. New speed: " + std::to_string(currentSpeed));
}