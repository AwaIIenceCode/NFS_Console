// Created by AwallencePC on 26.03.2025.
//

#ifndef NFS_CONSOLE_OBSTACLEMANAGER_H
#define NFS_CONSOLE_OBSTACLEMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../Config/Settings/GameConfig.h"
#include "../../Config/Utils/Logger.h"
#include "../../Domain/Entities/Obstacle.h"
#include "../../Domain/Entities/PlayerCar.h"
#include "SpeedEffectManager.h"
#include "../Managers/Interfaces/SpeedController.h"

class ObstacleManager {
public:
    ObstacleManager(float roadWidth, SpeedController* speedController);
    void initialize();
    void update(float deltaTime, float currentSpeed, bool isCountingDown, bool isPaused);
    void checkCollisions(PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed);
    void render(Renderer& renderer);

private:
    void spawnObstacle();

    float roadWidth;
    std::vector<Obstacle> obstacles;
    float obstacleSpawnInterval;
    sf::Clock obstacleSpawnClock;
    SpeedController* speedController;
};

#endif //NFS_CONSOLE_OBSTACLEMANAGER_H