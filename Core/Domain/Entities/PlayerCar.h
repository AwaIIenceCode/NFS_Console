//
// Created by AwallencePC on 18.03.2025.
// PlayerCar: Машина игрока, наследуется от Car (управление через InputHandler).
//

#ifndef PLAYERCAR_H
#define PLAYERCAR_H

#include <cmath>
#include "Car.h"

class PlayerCar : public Car
{
public:
    PlayerCar(const std::string& texturePath);
    void update(float deltaTime) override;

private:
    float acceleration; // Ускорение
    float rotationSpeed; // Скорость поворота
};



#endif //PLAYERCAR_H
