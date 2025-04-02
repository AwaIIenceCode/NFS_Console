// Created by AwallencePC on 26.03.2025.
//

#include "SpeedEffectManager.h"

SpeedEffectManager::SpeedEffectManager(float initialSpeed)
    : initialSpeed(initialSpeed) {}

void SpeedEffectManager::update(float deltaTime, float& currentSpeed, float baseSpeed)
{
    if (boostEffect.isActive)
    {
        boostEffect.timer += deltaTime;

        if (boostEffect.timer >= boostEffect.duration)
        {
            boostEffect.isActive = false;
            currentSpeed = boostEffect.preEffectSpeed; // Восстанавливаем скорость после ускорения
            Logger::getInstance().log("Boost effect ended. Speed restored to " + std::to_string(currentSpeed));
        }
    }

    if (slowdownEffect.isActive)
    {
        slowdownEffect.timer += deltaTime;

        if (slowdownEffect.timer >= slowdownEffect.duration)
        {
            slowdownEffect.isActive = false;
            Logger::getInstance().log("Slowdown effect ended. Speed remains at " + std::to_string(currentSpeed));
        }
    }
}

void SpeedEffectManager::applyBoost(float& currentSpeed)
{
    boostEffect.preEffectSpeed = currentSpeed;
    boostEffect.isActive = true;
    slowdownEffect.isActive = false;
    boostEffect.timer = 0.0f;
    currentSpeed *= boostEffect.multiplier;
    Logger::getInstance().log("Boost applied. New speed: " + std::to_string(currentSpeed));
}

void SpeedEffectManager::applySlowdown(float& currentSpeed)
{
    slowdownEffect.isActive = true;
    boostEffect.isActive = false;
    slowdownEffect.timer = 0.0f;
    currentSpeed *= slowdownEffect.multiplier;
    Logger::getInstance().log("Slowdown applied. New speed: " + std::to_string(currentSpeed));
}