// Created by AwallencePC on 30.03.2025.
//

#ifndef TRAFFICCAR_H
#define TRAFFICCAR_H

#include "Car.h"
#include "../SpawnableEntity.h"
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Config/Utils/Logger.h"
#include "Core/Config/Utils/ScaleManager.h"

class TrafficCar : public Car, public SpawnableEntity
{
public:
    TrafficCar(const std::string& texturePath, float roadLeft, float roadRight);
    void update(float deltaTime, float roadSpeed) override;
    void render(Renderer& renderer) const override;
    sf::FloatRect getBounds() const override;
    bool isOffScreen() const override;
    sf::Vector2f getPosition() const override;

private:
    float trafficSpeed;
    float scaleFactor;
};

#endif //TRAFFICCAR_H