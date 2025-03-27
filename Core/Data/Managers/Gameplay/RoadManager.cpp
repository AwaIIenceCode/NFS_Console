//
// Created by AwallencePC on 26.03.2025.
//

#include "RoadManager.h"
#include "../../../Config/Utils/Logger.h"
#include "../../../Config/Settings/GameConfig.h"

RoadManager::RoadManager() : roadWidth(0.0f), roadHeight(0.0f) {}

void RoadManager::initialize()
{
    if (!roadTexture.loadFromFile("Assets/Textures/TimeTrialRoad.png"))
    {
        Logger::getInstance().log("Failed to load road texture");
        sf::Image image;
        image.create(400, 800, sf::Color(100, 100, 100, 255));

        if (!roadTexture.loadFromImage(image))
        {
            Logger::getInstance().log("Failed to create road texture placeholder");
        }
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

    road1.setPosition(0.0f, -roadHeight + windowHeight);
    road2.setPosition(0.0f, -roadHeight * 2.0f + windowHeight);

    Logger::getInstance().log("Window width: " + std::to_string(windowWidth));
    Logger::getInstance().log("Window height: " + std::to_string(windowHeight));
    Logger::getInstance().log("Road width after scaling: " + std::to_string(roadWidth));
    Logger::getInstance().log("Road height after scaling: " + std::to_string(roadHeight));
    Logger::getInstance().log("road1 position: (" + std::to_string(road1.getPosition().x) + ", " + std::to_string(road1.getPosition().y) + ")");
    Logger::getInstance().log("road2 position: (" + std::to_string(road2.getPosition().x) + ", " + std::to_string(road2.getPosition().y) + ")");
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