// Created by AwallencePC on 18.03.2025.
//

#include "PlayerCar.h"

PlayerCar::PlayerCar(const std::string& texturePath)
    : Car(texturePath), moveSpeed(300.0f), scaleFactor(0.2f)
{
    ScaleManager::getInstance().scaleSprite(sprite);
    sprite.setScale(sprite.getScale().x * scaleFactor, sprite.getScale().y * scaleFactor);
}

void PlayerCar::updatePosition(float deltaTime, float roadLeft, float roadRight)
{
    float moveX = 0.0f;
    float adjustedMoveSpeed = moveSpeed;
    if (GameConfig::getInstance().isFullscreen()) {
        adjustedMoveSpeed *= 1.3f;  // Увеличиваем скорость поворота в полноэкранном режиме
    }

    GameConfig::ControlScheme scheme = GameConfig::getInstance().getControlScheme();
    InputHandler& input = InputHandler::getInstance();

    if (scheme == GameConfig::ControlScheme::WASD)
    {
        if (input.isKeyPressed(sf::Keyboard::A))
        {
            moveX -= adjustedMoveSpeed * deltaTime;
        }

        if (input.isKeyPressed(sf::Keyboard::D))
        {
            moveX += adjustedMoveSpeed * deltaTime;
        }
    }

    else if (scheme == GameConfig::ControlScheme::ARROWS)
    {
        if (input.isKeyPressed(sf::Keyboard::Left))
        {
            moveX -= adjustedMoveSpeed * deltaTime;
        }

        if (input.isKeyPressed(sf::Keyboard::Right))
        {
            moveX += adjustedMoveSpeed * deltaTime;
        }
    }

    sprite.move(moveX, 0.0f);

    float sidewalkWidth = 100.0f;
    float extraOffset = 17.5f;
    float carWidth = sprite.getGlobalBounds().width;
    float fullscreenOffset = GameConfig::getInstance().isFullscreen() ? carWidth * 1.5f : 0.0f;

    if (sprite.getPosition().x - carWidth / 2.0f < roadLeft + sidewalkWidth + extraOffset + fullscreenOffset)
    {
        sprite.setPosition(roadLeft + sidewalkWidth + extraOffset + fullscreenOffset + carWidth / 2.0f, sprite.getPosition().y);
    }

    if (sprite.getPosition().x + carWidth / 2.0f > roadRight - sidewalkWidth - extraOffset - fullscreenOffset)
    {
        sprite.setPosition(roadRight - sidewalkWidth - extraOffset - fullscreenOffset - carWidth / 2.0f, sprite.getPosition().y);
    }
}

void PlayerCar::update(float deltaTime, float roadSpeed, float speedMultiplier)
{
    // Реализация метода, если требуется
    // Например, можно оставить пустым, если PlayerCar не двигается по Y
}

void PlayerCar::render(Renderer& renderer) const
{
    renderer.render(sprite);
}

sf::FloatRect PlayerCar::getBounds() const
{
    return sprite.getGlobalBounds();
}

bool PlayerCar::isOffScreen() const
{
    return sprite.getPosition().y > GameConfig::getInstance().getWindowHeight();
}

sf::Vector2f PlayerCar::getPosition() const
{
    return sprite.getPosition();
}