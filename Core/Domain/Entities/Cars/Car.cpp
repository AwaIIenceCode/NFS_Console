//
// Created by AwallencePC on 18.03.2025.
//

#include "Car.h"
#include "../../Rendering/TextureManager.h"
#include "../../../Config/Utils/Logger.h"

Car::Car(const std::string& texturePath) : speed(200.0f)
{
    sf::Texture* texture = TextureManager::getInstance().loadTexture(texturePath);

    if (texture)
    {
        sprite.setTexture(*texture);
        sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
    }

    else
    {
        Logger::getInstance().log("Failed to load car texture: " + texturePath);
    }
}

void Car::update(float deltaTime) {}

void Car::render(Renderer& renderer)
{
    renderer.render(sprite);
}

sf::FloatRect Car::getBounds() const
{
    return sprite.getGlobalBounds();
}