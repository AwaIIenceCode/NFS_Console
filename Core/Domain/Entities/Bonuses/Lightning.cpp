// Created by AwallencePC on 25.03.2025.
//

#include "Lightning.h"
#include "Core/Domain/Rendering/Renderer.h"
#include "../../../Config/Utils/Logger.h"
#include <random>
#include "../../../Config/Settings/GameConfig.h"

Lightning::Lightning(const std::string& texturePath, float roadLeft, float roadRight)
{
    sf::Texture* texture = TextureManager::getInstance().loadTexture(texturePath);

    if (!texture)
    {
        Logger::getInstance().log("Failed to load lightning texture: " + texturePath);
        sf::Image image;

        image.create(30, 30, sf::Color::Yellow);
        sf::Texture placeholder;

        if (!placeholder.loadFromImage(image))
        {
            Logger::getInstance().log("Failed to create lightning texture placeholder");
        }

        else
        {
            texture = TextureManager::getInstance().addTexture(texturePath + "_placeholder", placeholder);
        }
    }

    else
    {
        Logger::getInstance().log("Successfully loaded lightning texture: " + texturePath);
    }

    sprite.setTexture(*texture);
    float baseScale = 0.07f;
    float scaleMultiplier = GameConfig::getInstance().isFullscreen() ? 1.5f : 1.0f;
    sprite.setScale(baseScale * scaleMultiplier, baseScale * scaleMultiplier);

    float textureWidth = texture->getSize().x * sprite.getScale().x;
    float sidewalkWidth = 100.0f;
    float spawnMargin = 60.0f;
    float adjustedRoadLeft = roadLeft + sidewalkWidth + spawnMargin;
    float adjustedRoadRight = roadRight - sidewalkWidth - spawnMargin - textureWidth;
    float spawnRange = adjustedRoadRight - adjustedRoadLeft;

    if (spawnRange < 0)
    {
        Logger::getInstance().log("Warning: spawnRange is negative (" + std::to_string(spawnRange) + "), adjusting to 0");
        spawnRange = 0;
    }

    float xPos = adjustedRoadLeft + static_cast<float>(rand()) / RAND_MAX * spawnRange;

    Logger::getInstance().log("Generated xPos: " + std::to_string(xPos) +
                             ", range: [" + std::to_string(adjustedRoadLeft) + ", " +
                             std::to_string(adjustedRoadRight) + "]");

    sprite.setPosition(xPos, 0.0f);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    Logger::getInstance().log("Lightning created with bounds: (left: " + std::to_string(bounds.left) +
                             ", top: " + std::to_string(bounds.top) +
                             ", width: " + std::to_string(bounds.width) +
                             ", height: " + std::to_string(bounds.height) + ")");
}

sf::Vector2f Lightning::getPosition() const
{
    return sprite.getPosition();
}

void Lightning::update(float deltaTime, float roadSpeed, float speedMultiplier)
{
    float adjustedSpeed = roadSpeed / speedMultiplier;
    sprite.move(0.0f, adjustedSpeed * deltaTime);
}

bool Lightning::isOffScreen() const
{
    float yPos = sprite.getPosition().y;
    float windowHeight = GameConfig::getInstance().getWindowHeight();
    bool offScreen = yPos > windowHeight;
    return offScreen;
}

void Lightning::render(Renderer& renderer) const
{
    renderer.render(sprite);
}

sf::FloatRect Lightning::getBounds() const
{
    return sprite.getGlobalBounds();
}