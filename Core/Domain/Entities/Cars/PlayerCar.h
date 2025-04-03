//
// Created by AwallencePC on 18.03.2025.
//

#ifndef PLAYERCAR_H
#define PLAYERCAR_H

#include <cmath>
#include "Car.h"
#include "../../../UI/Input/InputHandler.h"

class PlayerCar : public Car
{
public:
    PlayerCar(const std::string& texturePath);
    void update(float deltaTime, float roadLeft, float roadRight);

private:
    float moveSpeed;
    float scaleFactor;
};

#endif //PLAYERCAR_H