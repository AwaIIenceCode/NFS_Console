//
// Created by AwallencePC on 26.03.2025.
//

#ifndef NFS_CONSOLE_ROADMANAGER_H
#define NFS_CONSOLE_ROADMANAGER_H

#include <SFML/Graphics.hpp>
#include "../../../Domain/Rendering/Renderer.h"

class RoadManager
{
public:
    RoadManager();
    void initialize();
    void update(float deltaTime, float currentSpeed, bool isCountingDown, bool isPaused);
    void render(Renderer& renderer);

    float getRoadWidth() const { return roadWidth; }
    float getRoadHeight() const { return roadHeight; }

private:
    sf::Sprite road1, road2;
    sf::Texture roadTexture;
    float roadWidth, roadHeight;
};

#endif //NFS_CONSOLE_ROADMANAGER_H