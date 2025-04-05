//
// Created by AwallencePC on 18.03.2025.
//

#ifndef PLAYERCAR_H
#define PLAYERCAR_H

#include "Car.h"
#include "../SpawnableEntity.h"
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Config/Utils/Logger.h"
#include "Core/Config/Utils/ScaleManager.h"
#include "../../../UI/Input/InputHandler.h"

class PlayerCar : public Car, public SpawnableEntity
{
public:
    PlayerCar(const std::string& texturePath);
    void updatePosition(float deltaTime, float roadLeft, float roadRight);  // Переименовываем
    void update(float deltaTime, float roadSpeed, float speedMultiplier) override;
    void render(Renderer& renderer) const override;
    sf::FloatRect getBounds() const override;
    bool isOffScreen() const override;
    sf::Vector2f getPosition() const override;

private:
    float moveSpeed;
    float scaleFactor;
};

#endif //PLAYERCAR_H