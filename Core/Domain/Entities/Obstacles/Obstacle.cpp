// Created by AwallencePC on 26.03.2025.
//

#include "Obstacle.h"
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Config/Utils/Logger.h"

Obstacle::Obstacle(const std::string& texturePath, float roadLeft, float roadRight) : speed(0.0f) {
    if (!texture.loadFromFile(texturePath)) {
        Logger::getInstance().log("Failed to load obstacle texture: " + texturePath);
        sf::Image image;
        image.create(30, 30, sf::Color::Red); // Заглушка: красный квадрат
        if (!texture.loadFromImage(image)) {
            Logger::getInstance().log("Failed to create obstacle texture placeholder");
        }
    }

    sprite.setTexture(texture);
    float textureWidth = static_cast<float>(texture.getSize().x);
    float textureHeight = static_cast<float>(texture.getSize().y);
    sprite.setOrigin(textureWidth / 2.0f, textureHeight / 2.0f);

    // Уменьшаем размер камушка до 30x30 пикселей
    float desiredWidth = 50.0f;
    float desiredHeight = 50.0f;
    float scaleX = desiredWidth / textureWidth;
    float scaleY = desiredHeight / textureHeight;
    sprite.setScale(scaleX, scaleY);

    float spawnMargin = 60.0f;
    float adjustedRoadLeft = roadLeft + spawnMargin + (desiredWidth / 1.0f);
    float adjustedRoadRight = roadRight - spawnMargin - (desiredWidth / 1.0f);
    float spawnRange = adjustedRoadRight - adjustedRoadLeft;
    if (spawnRange < 0) spawnRange = 0; // Защита от отрицательного диапазона
    float xPos = adjustedRoadLeft + static_cast<float>(rand() % static_cast<int>(spawnRange));
    sprite.setPosition(xPos, -desiredHeight);
}

void Obstacle::update(float deltaTime, float roadSpeed) {
    speed = roadSpeed;
    sprite.move(0.0f, speed * deltaTime);
}

void Obstacle::render(Renderer& renderer) const {
    renderer.render(sprite);
}

sf::FloatRect Obstacle::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Obstacle::isOffScreen() const {
    return sprite.getPosition().y > GameConfig::getInstance().getWindowHeight() + sprite.getGlobalBounds().height;
}

sf::Vector2f Obstacle::getPosition() const {
    return sprite.getPosition();
}