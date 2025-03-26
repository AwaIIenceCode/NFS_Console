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

// Предварительное объявление класса GameplayState
class GameplayState;

class ObstacleManager {
public:
    ObstacleManager(float roadWidth, GameplayState* gameplayState); // Добавляем указатель на GameplayState
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
    GameplayState* gameplayState; // Указатель на GameplayState
};

#endif //NFS_CONSOLE_OBSTACLEMANAGER_H