//
// Created by AwallencePC on 18.03.2025.
//

#include "PlayerCar.h"

PlayerCar::PlayerCar(const std::string& texturePath)
    : Car(texturePath), acceleration(300.0f), rotationSpeed(180.0f) {}

void PlayerCar::update(float deltaTime)
{
    // Управление
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // Движение вперёд
        float rad = rotation * 3.14159f / 180.0f; // Градусы в радианы
        float moveX = std::cos(rad) * speed * deltaTime;
        float moveY = std::sin(rad) * speed * deltaTime;
        sprite.move(moveX, moveY);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // Движение назад
        float rad = rotation * 3.14159f / 180.0f;
        float moveX = std::cos(rad) * speed * deltaTime;
        float moveY = std::sin(rad) * speed * deltaTime;
        sprite.move(-moveX, -moveY);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // Поворот влево
        rotation -= rotationSpeed * deltaTime;
        sprite.setRotation(rotation);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // Поворот вправо
        rotation += rotationSpeed * deltaTime;
        sprite.setRotation(rotation);
    }
}