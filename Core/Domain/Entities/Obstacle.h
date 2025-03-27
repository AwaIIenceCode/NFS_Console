// Created by AwallencePC on 19.03.2025.
//

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SpawnableEntity.h"
#include "../../Config/Settings/GameConfig.h"
#include "../../Config/Utils/Logger.h"

class Obstacle : public SpawnableEntity {
public:
    Obstacle(const std::string& texturePath, float roadLeft, float roadRight);
    void update(float deltaTime, float roadSpeed) override;
    void render(Renderer& renderer) const override;
    sf::FloatRect getBounds() const override;
    bool isOffScreen() const override;
    sf::Vector2f getPosition() const override;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
};

#endif //OBSTACLE_H