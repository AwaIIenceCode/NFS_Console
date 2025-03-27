// Created by AwallencePC on 26.03.2025.
//

#include "ObstacleManager.h"

ObstacleManager::ObstacleManager(float roadWidth, SpeedController* speedController)
    : roadWidth(roadWidth), obstacleSpawnInterval(6.0f), speedController(speedController) {}

void ObstacleManager::initialize() {
    Logger::getInstance().log("ObstacleManager initialized with spawn interval: " + std::to_string(obstacleSpawnInterval));
}

void ObstacleManager::update(float deltaTime, float currentSpeed, bool isCountingDown, bool isPaused) {
    if (!isCountingDown && !isPaused) {
        for (auto it = obstacles.begin(); it != obstacles.end();) {
            it->update(deltaTime, currentSpeed);
            if (it->isOffScreen()) {
                Logger::getInstance().log("Obstacle position before removal: (" +
                                         std::to_string(it->getPosition().x) + ", " +
                                         std::to_string(it->getPosition().y) + ")");
                Logger::getInstance().log("Obstacle removed: off screen");
                it = obstacles.erase(it);
            } else {
                ++it;
            }
        }

        float elapsed = obstacleSpawnClock.getElapsedTime().asSeconds();
        if (elapsed >= obstacleSpawnInterval) {
            spawnObstacle();
            obstacleSpawnClock.restart();
        }
    }
}

void ObstacleManager::spawnObstacle() {
    float roadLeft = (GameConfig::getInstance().getWindowWidth() - roadWidth) / 2.0f;
    float roadRight = roadLeft + roadWidth;
    Logger::getInstance().log("Spawning obstacle at roadLeft: " + std::to_string(roadLeft) +
                             ", roadRight: " + std::to_string(roadRight));
    obstacles.emplace_back("Assets/Textures/Rock.png", roadLeft, roadRight);
    Logger::getInstance().log("Spawned an obstacle");
}

void ObstacleManager::checkCollisions(PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed) {
    sf::FloatRect playerBounds = playerCar.getBounds();
    for (auto it = obstacles.begin(); it != obstacles.end();) {
        sf::FloatRect obstacleBounds = it->getBounds();
        if (playerBounds.intersects(obstacleBounds)) {
            Logger::getInstance().log("Player hit an obstacle! Applying speed reduction.");
            speedEffectManager.applySlowdown(currentSpeed);
            speedController->resetAcceleration();
            it = obstacles.erase(it);
        } else {
            ++it;
        }
    }
}

void ObstacleManager::render(Renderer& renderer) {
    for (const auto& obstacle : obstacles) {
        obstacle.render(renderer);
    }
}