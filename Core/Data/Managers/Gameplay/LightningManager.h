//
// Created by AwallencePC on 26.03.2025.
//

#ifndef LIGHTNINGMANAGER_H
#define LIGHTNINGMANAGER_H

#include <SFML/Graphics.hpp>
#include "SpeedEffectManager.h"
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Config/Utils/Logger.h"
#include "../../../Domain/Entities/Bonuses/Lightning.h"
#include "../../../Domain/Entities/Cars/PlayerCar.h"

class PlayerCar;

class LightningManager
{
public:
    LightningManager(float roadWidth);
    void initialize();
    void update(float deltaTime, float currentSpeed, float speedMultiplier, bool isCountingDown, bool isPaused);
    void checkCollisions(PlayerCar& playerCar, SpeedEffectManager& boostManager, float& currentSpeed);
    void render(Renderer& renderer);

private:
    void spawnLightning();

    float roadWidth;
    std::vector<Lightning> lightnings;
    float lightningSpawnInterval;
    sf::Clock lightningSpawnClock;
};

#endif //LIGHTNINGMANAGER_H