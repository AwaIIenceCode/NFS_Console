//
// Created by AwallencePC on 19.03.2025.
// Obstacle: Препятствие на трассе (например, камни, барьеры).
//

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include "../Rendering/Renderer.h"

class Obstacle
{
public:
    Obstacle(const std::string& texturePath, float roadLeft, float roadRight);
    void update(float deltaTime, float roadSpeed);
    void render(Renderer& renderer) const;
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
};



#endif //OBSTACLE_H
