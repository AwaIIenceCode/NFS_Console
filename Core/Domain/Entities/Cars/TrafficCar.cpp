// Created by AwallencePC on 30.03.2025.
//

#include "TrafficCar.h"
#include <cstdlib>
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Config/Utils/Logger.h"

TrafficCar::TrafficCar(const std::string& texturePath, float roadLeft, float roadRight)
    : Car(texturePath), scaleFactor(0.2f) {
    trafficSpeed = 300.0f + static_cast<float>(rand() % 451);
    Logger::getInstance().log("TrafficCar spawned with speed: " + std::to_string(trafficSpeed));

    ScaleManager::getInstance().scaleSprite(sprite);
    sprite.setScale(sprite.getScale().x * scaleFactor, sprite.getScale().y * scaleFactor);

    float sidewalkWidth = 100.0f;
    float carWidth = sprite.getGlobalBounds().width;
    float spawnMargin = 120.0f;
    float adjustedRoadLeft = roadLeft + sidewalkWidth + spawnMargin + (carWidth / 2.0f);
    float adjustedRoadRight = roadRight - sidewalkWidth - spawnMargin - (carWidth / 2.0f);
    float spawnRange = adjustedRoadRight - adjustedRoadLeft;

    if (spawnRange < 0) spawnRange = 0;

    float xPos = adjustedRoadLeft + static_cast<float>(rand() % static_cast<int>(spawnRange));
    sprite.setPosition(xPos, -sprite.getGlobalBounds().height);

    Logger::getInstance().log("TrafficCar spawned at x: " + std::to_string(xPos));
}

void TrafficCar::update(float deltaTime, float roadSpeed, float speedMultiplier)
{
    float adjustedTrafficSpeed = trafficSpeed / speedMultiplier;  // Корректируем скорость трафика
    sprite.move(0.0f, adjustedTrafficSpeed * deltaTime);
}

void TrafficCar::render(Renderer& renderer) const
{
    renderer.render(sprite);
}

sf::FloatRect TrafficCar::getBounds() const
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float widthShrinkFactor = 0.2f;
    float heightShrinkFactor = 0.6f;
    float newWidth = bounds.width * (1.0f - widthShrinkFactor);
    float newHeight = bounds.height * (1.0f - heightShrinkFactor);
    float newLeft = bounds.left + (bounds.width - newWidth) / 2.0f;
    float newTop = bounds.top + (bounds.height - newHeight) / 2.0f;
    return sf::FloatRect(newLeft, newTop, newWidth, newHeight);
}

bool TrafficCar::isOffScreen() const
{
    return sprite.getPosition().y > GameConfig::getInstance().getWindowHeight() + sprite.getGlobalBounds().height;
}

sf::Vector2f TrafficCar::getPosition() const
{
    return sprite.getPosition();
}