// Created by AwallencePC on 27.03.2025.
//

#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "../../Config/Settings/GameConfig.h"
#include "../../Config/Utils/Logger.h"
#include "../../Domain/Rendering/Renderer.h"

class HUD {
public:
    HUD(float totalDistance);
    void initialize();
    void updateTimer(float elapsedTime);
    void updateProgress(float passedDistance);
    void updateSpeedometer(float currentSpeed);
    void render(Renderer& renderer);

private:
    float totalDistance;
    sf::Text timerText;
    sf::Text progressText;
    sf::Text speedText;
    sf::Font font;
};

#endif //HUD_H