// Created by AwallencePC on 18.03.2025.
//

#include "../../../Domain/Entities/Cars/PlayerCar.h"
#include "../../../Config/Utils/ScaleManager.h"
#include "../../../Config/Settings/GameConfig.h"

PlayerCar::PlayerCar(const std::string& texturePath)
    : Car(texturePath), moveSpeed(300.0f), scaleFactor(0.2f) {
    ScaleManager::getInstance().scaleSprite(sprite);
    sprite.setScale(sprite.getScale().x * scaleFactor, sprite.getScale().y * scaleFactor);
}

void PlayerCar::update(float deltaTime, float roadLeft, float roadRight) {
    float moveX = 0.0f;

    // Проверяем текущую схему управления
    GameConfig::ControlScheme scheme = GameConfig::getInstance().getControlScheme();
    InputHandler& input = InputHandler::getInstance();
    if (scheme == GameConfig::ControlScheme::WASD) {
        if (input.isKeyPressed(sf::Keyboard::A)) {
            moveX -= moveSpeed * deltaTime;
        }
        if (input.isKeyPressed(sf::Keyboard::D)) {
            moveX += moveSpeed * deltaTime;
        }
    } else if (scheme == GameConfig::ControlScheme::ARROWS) {
        if (input.isKeyPressed(sf::Keyboard::Left)) {
            moveX -= moveSpeed * deltaTime;
        }
        if (input.isKeyPressed(sf::Keyboard::Right)) {
            moveX += moveSpeed * deltaTime;
        }
    }

    sprite.move(moveX, 0.0f);

    // Ограничиваем движение машины пределами дороги с учётом тротуаров и дополнительного отступа
    float sidewalkWidth = 100.0f;
    float extraOffset = 17.5f;
    float carWidth = sprite.getGlobalBounds().width;
    if (sprite.getPosition().x - carWidth / 2.0f < roadLeft + sidewalkWidth + extraOffset) {
        sprite.setPosition(roadLeft + sidewalkWidth + extraOffset + carWidth / 2.0f, sprite.getPosition().y);
    }
    if (sprite.getPosition().x + carWidth / 2.0f > roadRight - sidewalkWidth - extraOffset) {
        sprite.setPosition(roadRight - sidewalkWidth - extraOffset - carWidth / 2.0f, sprite.getPosition().y);
    }
}