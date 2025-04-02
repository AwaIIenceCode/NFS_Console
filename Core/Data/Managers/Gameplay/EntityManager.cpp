// Created by AwallencePC on 26.03.2025.
//

#include "EntityManager.h"
#include <Core/Config/Settings/GameConfig.h>

EntityManager::EntityManager(float roadWidth, float spawnInterval, SpawnFunction spawnFunc, CollisionHandler collisionHandler, SpeedController* speedController)
    : roadWidth(roadWidth), spawnInterval(spawnInterval), spawnFunction(spawnFunc), collisionHandler(collisionHandler), speedController(speedController) {}

void EntityManager::initialize()
{
    Logger::getInstance().log("EntityManager initialized with spawn interval: " + std::to_string(spawnInterval));
}

void EntityManager::update(float deltaTime, float currentSpeed, bool isCountingDown, bool isPaused)
{
    if (!isCountingDown && !isPaused)
    {
        for (auto it = entities.begin(); it != entities.end();)
        {
            (*it)->update(deltaTime, currentSpeed);

            if ((*it)->isOffScreen())
            {
                Logger::getInstance().log("Entity position before removal: (" +
                                         std::to_string((*it)->getPosition().x) + ", " +
                                         std::to_string((*it)->getPosition().y) + ")");
                Logger::getInstance().log("Entity removed: off screen");
                it = entities.erase(it);
            }

            else { ++it; }
        }

        float elapsed = spawnClock.getElapsedTime().asSeconds();

        if (elapsed >= spawnInterval)
        {
            spawnEntity();
            spawnClock.restart();
        }
    }
}

void EntityManager::spawnEntity()
{
    float roadLeft = (GameConfig::getInstance().getWindowWidth() - roadWidth) / 2.0f;
    float roadRight = roadLeft + roadWidth;
    Logger::getInstance().log("Spawning entity at roadLeft: " + std::to_string(roadLeft) +
                             ", roadRight: " + std::to_string(roadRight));
    entities.push_back(spawnFunction(roadLeft, roadRight));
    Logger::getInstance().log("Spawned an entity");
}

void EntityManager::checkCollisions(PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed)
{
    collisionHandler(playerCar, speedEffectManager, currentSpeed, speedController, entities);
}

void EntityManager::render(Renderer& renderer)
{
    for (const auto& entity : entities)
    {
        entity->render(renderer);
    }
}