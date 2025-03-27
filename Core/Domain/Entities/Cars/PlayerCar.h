//
// Created by AwallencePC on 18.03.2025.
// PlayerCar: Машина игрока, наследуется от Car (управление через InputHandler).
//

#ifndef PLAYERCAR_H
#define PLAYERCAR_H

#include <cmath>
#include "Car.h"
#include "../../../UI/Input/InputHandler.h"

class PlayerCar : public Car {
public:
    PlayerCar(const std::string& texturePath);
    void update(float deltaTime, float roadLeft, float roadRight); // Оставляем только этот метод

private:
    float moveSpeed; // Скорость движения влево/вправо
    float scaleFactor; // Масштаб текстуры
};

#endif //PLAYERCAR_H