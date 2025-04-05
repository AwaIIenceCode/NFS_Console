//
// Created by AwallencePC on 26.03.2025.
//

#include "../../../Domain/Entities/Cars/PlayerCar.h"
#include "LightningManager.h"

LightningManager::LightningManager(float roadWidth)
    : roadWidth(roadWidth), lightningSpawnInterval(10.0f) {}

void LightningManager::initialize()
{
    Logger::getInstance().log("LightningManager initialized with spawn interval: " + std::to_string(lightningSpawnInterval));
}

void LightningManager::update(float deltaTime, float currentSpeed, float speedMultiplier, bool isCountingDown, bool isPaused)
{
    if (!isCountingDown && !isPaused)
    {
        for (auto it = lightnings.begin(); it != lightnings.end();)
        {
            it->update(deltaTime, currentSpeed, speedMultiplier);

            if (it->isOffScreen())
            {
                Logger::getInstance().log("Lightning position before removal: (" +
                                         std::to_string(it->getPosition().x) + ", " +
                                         std::to_string(it->getPosition().y) + ")");
                Logger::getInstance().log("Lightning removed: off screen");

                it = lightnings.erase(it);
            }

            else { ++it; }
        }

        float elapsed = lightningSpawnClock.getElapsedTime().asSeconds();

        if (elapsed >= lightningSpawnInterval)
        {
            spawnLightning();
            lightningSpawnClock.restart();
        }
    }
}

void LightningManager::spawnLightning()
{
    float roadLeft = (GameConfig::getInstance().getWindowWidth() - roadWidth) / 2.0f;
    float roadRight = roadLeft + roadWidth;
    Logger::getInstance().log("Spawning lightning at roadLeft: " + std::to_string(roadLeft) +
                             ", roadRight: " + std::to_string(roadRight));
    lightnings.emplace_back("J:/MyIDE/NFS_Console/Assets/Textures/Lightning.png", roadLeft, roadRight);
    Logger::getInstance().log("Spawned a lightning");
}

void LightningManager::checkCollisions(PlayerCar& playerCar, SpeedEffectManager& boostManager, float& currentSpeed)
{
    sf::FloatRect playerBounds = playerCar.getBounds();

    for (auto it = lightnings.begin(); it != lightnings.end();)
    {
        sf::FloatRect lightningBounds = it->getBounds();
        if (playerBounds.intersects(lightningBounds))
        {
            Logger::getInstance().log("Player picked up a lightning! Applying speed boost.");
            boostManager.applyBoost(currentSpeed);
            it = lightnings.erase(it);
        }

        else { ++it; }
    }
}

void LightningManager::render(Renderer& renderer)
{
    for (const auto& lightning : lightnings) { lightning.render(renderer); }
}