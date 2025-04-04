//
// Created by AwallencePC on 26.03.2025.
//

#include "RoadManager.h"
#include "../../../Config/Utils/Logger.h"
#include "../../../Config/Settings/GameConfig.h"

RoadManager::RoadManager() : roadWidth(0.0f), roadHeight(0.0f) {}

void RoadManager::initialize()
{

    if (!roadTexture.loadFromFile("J:/MyIDE/NFS_Console/Assets/Textures/TimeTrialRoad.png"))
    {
        Logger::getInstance().log("Failed to load road texture");
        sf::Image image;
        image.create(400, 800, sf::Color(100, 100, 100, 255));
        roadTexture.loadFromImage(image);
    }

    road1.setTexture(roadTexture);
    road2.setTexture(roadTexture);

    float textureWidth = static_cast<float>(roadTexture.getSize().x);
    float textureHeight = static_cast<float>(roadTexture.getSize().y);

    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float windowHeight = static_cast<float>(GameConfig::getInstance().getWindowHeight());

    float scaleX = windowWidth / textureWidth;
    float scaleY = windowHeight / textureHeight;
    road1.setScale(scaleX, scaleY);
    road2.setScale(scaleX, scaleY);

    roadWidth = textureWidth * scaleX;
    roadHeight = textureHeight * scaleY;

    road1.setPosition(0.0f, 0.0f);
    road2.setPosition(0.0f, -roadHeight);
}

void RoadManager::update(float deltaTime, float currentSpeed, bool isCountingDown, bool isPaused)
{
    if (!isCountingDown && !isPaused)
    {
        float moveDistance = currentSpeed * deltaTime;
        road1.move(0.0f, moveDistance);
        road2.move(0.0f, moveDistance);

        float windowHeight = static_cast<float>(GameConfig::getInstance().getWindowHeight());

        if (road1.getPosition().y >= windowHeight)
        {
            road1.setPosition(road1.getPosition().x, road2.getPosition().y - roadHeight);
        }

        if (road2.getPosition().y >= windowHeight)
        {
            road2.setPosition(road2.getPosition().x, road1.getPosition().y - roadHeight);
        }
    }
}

void RoadManager::render(Renderer& renderer)
{
    renderer.render(road1);
    renderer.render(road2);
}