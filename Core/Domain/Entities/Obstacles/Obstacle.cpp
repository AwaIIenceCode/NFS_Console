// Created by AwallencePC on 26.03.2025.
//

#include "Obstacle.h"
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Config/Utils/Logger.h"

Obstacle::Obstacle(const std::string& texturePath, float roadLeft, float roadRight) : speed(0.0f) {
    sf::Texture* texture = TextureManager::getInstance().loadTexture(texturePath);

    if (!texture)
    {
        Logger::getInstance().log("Failed to load obstacle texture: " + texturePath);
        sf::Image image;
        image.create(30, 30, sf::Color::Red);
        sf::Texture placeholder;

        if (!placeholder.loadFromImage(image))
        {
            Logger::getInstance().log("Failed to create obstacle texture placeholder");
        }

        else
        {
            texture = TextureManager::getInstance().addTexture(texturePath + "_placeholder", placeholder);
        }
    }

    sprite.setTexture(*texture);
    float textureWidth = static_cast<float>(texture->getSize().x);
    float textureHeight = static_cast<float>(texture->getSize().y);
    sprite.setOrigin(textureWidth / 2.0f, textureHeight / 2.0f);

    float desiredWidth = 50.0f;
    float desiredHeight = 50.0f;
    float scaleMultiplier = GameConfig::getInstance().isFullscreen() ? 1.5f : 1.0f;  // Увеличиваем размер в полноэкранном режиме
    float scaleX = (desiredWidth / textureWidth) * scaleMultiplier;
    float scaleY = (desiredHeight / textureHeight) * scaleMultiplier;
    sprite.setScale(scaleX, scaleY);

    float spawnMargin = 200.0f;
    float adjustedRoadLeft = roadLeft + spawnMargin + (desiredWidth * scaleMultiplier / 2.0f);
    float adjustedRoadRight = roadRight - spawnMargin - (desiredWidth * scaleMultiplier / 2.0f);
    float spawnRange = adjustedRoadRight - adjustedRoadLeft;
    if (spawnRange < 0) spawnRange = 0;
    float xPos = adjustedRoadLeft + static_cast<float>(rand() % static_cast<int>(spawnRange));

    sprite.setPosition(xPos, -desiredHeight * scaleMultiplier);
}

void Obstacle::update(float deltaTime, float roadSpeed, float speedMultiplier)
{
    float adjustedSpeed = roadSpeed + (roadSpeed * (speedMultiplier - 1.0f));
    sprite.move(0.0f, adjustedSpeed * deltaTime);
}

void Obstacle::render(Renderer& renderer) const
{
    renderer.render(sprite);
}

sf::FloatRect Obstacle::getBounds() const
{
    return sprite.getGlobalBounds();
}

bool Obstacle::isOffScreen() const
{
    return sprite.getPosition().y > GameConfig::getInstance().getWindowHeight() + sprite.getGlobalBounds().height;
}

sf::Vector2f Obstacle::getPosition() const
{
    return sprite.getPosition();
}