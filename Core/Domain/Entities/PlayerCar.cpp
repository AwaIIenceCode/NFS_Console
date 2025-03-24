//
// Created by AwallencePC on 18.03.2025.
//

#include "PlayerCar.h"

PlayerCar::PlayerCar(const std::string& texturePath)
    : Car(texturePath), moveSpeed(300.0f), scaleFactor(0.33f) { // Уменьшаем в 2 раза
    sprite.setScale(scaleFactor, scaleFactor);
}

void PlayerCar::update(float deltaTime) {}

void PlayerCar::update(float deltaTime, float roadLeft, float roadRight)
{
    float moveX = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { moveX -= moveSpeed * deltaTime; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { moveX += moveSpeed * deltaTime; }

    sprite.move(moveX, 0.0f);
}