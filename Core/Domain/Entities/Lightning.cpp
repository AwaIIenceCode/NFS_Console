// Created by AwallencePC on 25.03.2025.
//

#include "Lightning.h"
#include "Core/Domain/Rendering/Renderer.h"
#include "../../Config/Utils/Logger.h"
#include <random>
#include "../../Config/Settings/GameConfig.h"

Lightning::Lightning(const std::string& texturePath, float roadLeft, float roadRight) {
    if (!texture.loadFromFile(texturePath)) {
        Logger::getInstance().log("Failed to load lightning texture: " + texturePath);
        sf::Image image;
        image.create(30, 30, sf::Color::Yellow);
        if (!texture.loadFromImage(image)) {
            Logger::getInstance().log("Failed to create lightning texture placeholder");
        }
    } else {
        Logger::getInstance().log("Successfully loaded lightning texture: " + texturePath);
    }

    sprite.setTexture(texture);
    // Увеличиваем масштаб до 0.2f (20% от исходного размера)
    sprite.setScale(0.07f, 0.07f);

    // Новый способ генерации xPos с учётом тротуаров
    float textureWidth = texture.getSize().x * sprite.getScale().x;
    float sidewalkWidth = 100.0f; // Ширина тротуара с каждой стороны
    float spawnRange = (roadRight - sidewalkWidth) - (roadLeft + sidewalkWidth) - textureWidth;
    if (spawnRange < 0) {
        Logger::getInstance().log("Warning: spawnRange is negative (" + std::to_string(spawnRange) + "), adjusting to 0");
        spawnRange = 0;
    }
    float xPos = (roadLeft + sidewalkWidth) + static_cast<float>(rand()) / RAND_MAX * spawnRange;

    Logger::getInstance().log("Generated xPos: " + std::to_string(xPos) +
                             ", range: [" + std::to_string(roadLeft + sidewalkWidth) + ", " +
                             std::to_string(roadRight - sidewalkWidth - textureWidth) + "]");

    sprite.setPosition(xPos, 0.0f);

    // Логируем границы молнии после создания
    sf::FloatRect bounds = sprite.getGlobalBounds();
    Logger::getInstance().log("Lightning created with bounds: (left: " + std::to_string(bounds.left) +
                             ", top: " + std::to_string(bounds.top) +
                             ", width: " + std::to_string(bounds.width) +
                             ", height: " + std::to_string(bounds.height) + ")");
}

sf::Vector2f Lightning::getPosition() const {
    return sprite.getPosition();
}

void Lightning::update(float deltaTime, float roadSpeed) {
    sprite.move(0.0f, roadSpeed * deltaTime);
}

bool Lightning::isOffScreen() const {
    float yPos = sprite.getPosition().y;
    float windowHeight = GameConfig::getInstance().getWindowHeight();
    bool offScreen = yPos > windowHeight;
    return offScreen;
}

void Lightning::render(Renderer& renderer) const {
    renderer.render(sprite);
}

sf::FloatRect Lightning::getBounds() const {
    return sprite.getGlobalBounds();
}