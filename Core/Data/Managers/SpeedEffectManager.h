// Created by AwallencePC on 26.03.2025.
//

#ifndef SPEEDEFFECTMANAGER_H
#define SPEEDEFFECTMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../Config/Utils/Logger.h"

class SpeedEffectManager {
public:
    SpeedEffectManager(float initialSpeed);
    void update(float deltaTime, float& currentSpeed, float baseSpeed);
    void applyBoost(float& currentSpeed);
    void applySlowdown(float& currentSpeed);

private:
    struct BoostEffect {
        bool isActive;
        float timer;
        float duration;
        float multiplier;
        float preEffectSpeed;
        BoostEffect() : isActive(false), timer(0.0f), duration(1.5f), multiplier(1.5f), preEffectSpeed(0.0f) {}
    };

    struct SlowdownEffect {
        bool isActive;
        float timer;
        float duration;
        float multiplier; // Добавляем множитель для замедления
        SlowdownEffect() : isActive(false), timer(0.0f), duration(1.5f), multiplier(0.5f) {} // Замедление в 2 раза
    };

    BoostEffect boostEffect;
    SlowdownEffect slowdownEffect;
    float initialSpeed;
};

#endif //SPEEDEFFECTMANAGER_H