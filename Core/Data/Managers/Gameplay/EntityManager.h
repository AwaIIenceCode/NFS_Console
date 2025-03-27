// Created by AwallencePC on 26.03.2025.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include "../../../Domain/Entities/SpawnableEntity.h"
#include "../../../Domain/Entities/Cars/PlayerCar.h"
#include "../../Managers/Interfaces/SpeedController.h"
#include "../Gameplay/SpeedEffectManager.h"
#include <memory>

class EntityManager {
public:
    using SpawnFunction = std::function<std::unique_ptr<SpawnableEntity>(float, float)>;
    using CollisionHandler = std::function<void(PlayerCar&, SpeedEffectManager&, float&, SpeedController*, std::vector<std::unique_ptr<SpawnableEntity>>&)>;

    EntityManager(float roadWidth, float spawnInterval, SpawnFunction spawnFunc, CollisionHandler collisionHandler, SpeedController* speedController);
    void initialize();
    void update(float deltaTime, float currentSpeed, bool isCountingDown, bool isPaused);
    void checkCollisions(PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed);
    void render(Renderer& renderer);

private:
    void spawnEntity();

    float roadWidth;
    std::vector<std::unique_ptr<SpawnableEntity>> entities;
    float spawnInterval;
    sf::Clock spawnClock;
    SpawnFunction spawnFunction;
    CollisionHandler collisionHandler;
    SpeedController* speedController;
};

#endif //ENTITYMANAGER_H