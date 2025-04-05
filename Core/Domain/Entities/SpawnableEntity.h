// Created by AwallencePC on 27.03.2025.
//

#ifndef SPAWNABLEENTITY_H
#define SPAWNABLEENTITY_H

#include <SFML/Graphics.hpp>
#include "../Rendering/Renderer.h"

class SpawnableEntity
{
public:
    virtual ~SpawnableEntity() = default;
    virtual void update(float deltaTime, float roadSpeed, float speedMultiplier) = 0;
    virtual void render(Renderer& renderer) const = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual bool isOffScreen() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
};

#endif //SPAWNABLEENTITY_H