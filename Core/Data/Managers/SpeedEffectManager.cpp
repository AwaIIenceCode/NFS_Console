// Created by AwallencePC on 26.03.2025.
//

#include "SpeedEffectManager.h"

SpeedEffectManager::SpeedEffectManager(float initialSpeed)
    : isBoosted(false), isSlowed(false), effectDuration(1.5f), effectTimer(0.0f),
      boostMultiplier(1.5f), slowdownMultiplier(0.5f), initialSpeed(initialSpeed) {}

void SpeedEffectManager::update(float deltaTime, float& currentSpeed, float baseSpeed) {
    if (isBoosted || isSlowed) {
        effectTimer += deltaTime;
        if (effectTimer >= effectDuration) {
            isBoosted = false;
            isSlowed = false;
            currentSpeed = baseSpeed;
            Logger::getInstance().log("Speed effect ended. Speed returned to " + std::to_string(currentSpeed));
        }
    }
}

void SpeedEffectManager::applyBoost(float& currentSpeed) {
    isBoosted = true;
    isSlowed = false; // Отменяем замедление, если оно было
    effectTimer = 0.0f;
    currentSpeed *= boostMultiplier;
    Logger::getInstance().log("Boost applied. New speed: " + std::to_string(currentSpeed));
}

void SpeedEffectManager::applySlowdown(float& currentSpeed) {
    isSlowed = true;
    isBoosted = false; // Отменяем ускорение, если оно было
    effectTimer = 0.0f;
    currentSpeed = initialSpeed; // Сбрасываем скорость до начальной
    Logger::getInstance().log("Slowdown applied. Speed reset to " + std::to_string(currentSpeed));
}