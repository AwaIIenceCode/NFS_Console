//
// Created by AwallencePC on 18.03.2025.
// Car: Базовый класс для машин (общие данные: позиция, скорость, спрайт).
//

#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "../Rendering/Renderer.h"

class Car
{
public:
    Car(const std::string& texturePath);
    virtual ~Car() = default;

    virtual void update(float deltaTime);
    void render(Renderer& renderer);

    // Геттеры и сеттеры
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void setPosition(float x, float y) { sprite.setPosition(x, y); }
    sf::Sprite& getSprite() { return sprite; } // Для масштабирования

protected:
    sf::Sprite sprite;
    float speed;
    float rotation; // Угол поворота в градусах
};

#endif