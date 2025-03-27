// Created by AwallencePC on 26.03.2025.
//

#include "SpeedManager.h"

SpeedManager::SpeedManager(float initialSpeed, float baseSpeed, float accelerationTime)
    : initialSpeed(initialSpeed), baseSpeed(baseSpeed), accelerationTime(accelerationTime),
      currentSpeed(initialSpeed) {}

void SpeedManager::update(float deltaTime) {
    if (currentSpeed < baseSpeed) {
        // Рассчитываем скорость разгона: (baseSpeed - initialSpeed) / accelerationTime
        float speedIncreasePerSecond = (baseSpeed - initialSpeed) / accelerationTime;
        // Увеличиваем скорость пропорционально времени кадра (deltaTime)
        currentSpeed += speedIncreasePerSecond * deltaTime;
        if (currentSpeed > baseSpeed) {
            currentSpeed = baseSpeed;
        }
        Logger::getInstance().log("Speed updated to: " + std::to_string(currentSpeed));
    }
}

void SpeedManager::resetAcceleration() {
    currentSpeed = initialSpeed;
    accelerationTimer.restart();
    Logger::getInstance().log("Acceleration reset. Speed set to " + std::to_string(currentSpeed));
}

void SpeedManager::setCurrentSpeed(float newSpeed) {
    currentSpeed = newSpeed;
    Logger::getInstance().log("Speed manually set to: " + std::to_string(currentSpeed));
}