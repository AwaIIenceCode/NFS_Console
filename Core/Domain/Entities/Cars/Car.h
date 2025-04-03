//
// Created by AwallencePC on 18.03.2025.
//

#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "../../Rendering/Renderer.h"

class Car
{
public:
    Car(const std::string& texturePath);
    virtual ~Car() = default;

    virtual void update(float deltaTime);
    void render(Renderer& renderer);
    sf::FloatRect getBounds() const;

    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void setPosition(float x, float y) { sprite.setPosition(x, y); }
    sf::Sprite& getSprite() { return sprite; }

protected:
    sf::Sprite sprite;
    float speed;
    float rotation;
};

#endif //CAR_H