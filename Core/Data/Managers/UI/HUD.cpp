// Created by AwallencePC on 27.03.2025.
//

#include "HUD.h"
#include <sstream>
#include <iomanip>

HUD::HUD(float totalDistance) : totalDistance(totalDistance) {}

void HUD::initialize()
{
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float windowHeight = static_cast<float>(GameConfig::getInstance().getWindowHeight());

    float baseFontSize = windowHeight * 0.04f;
    float paddingX = windowWidth * 0.02f;
    float paddingY = windowHeight * 0.02f;

    timerText.setFont(font);
    timerText.setCharacterSize(static_cast<unsigned int>(baseFontSize));
    timerText.setPosition(paddingX, paddingY);

    progressText.setFont(font);
    progressText.setCharacterSize(static_cast<unsigned int>(baseFontSize));
    progressText.setPosition(paddingX, paddingY * 2 + baseFontSize);

    speedText.setFont(font);
    speedText.setCharacterSize(static_cast<unsigned int>(baseFontSize));
    speedText.setPosition(windowWidth - paddingX - speedText.getGlobalBounds().width, paddingY);
}

void HUD::updateTimer(float elapsedTime)
{
    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;
    int milliseconds = static_cast<int>(elapsedTime * 1000) % 1000 / 10;

    std::stringstream ss;

    ss << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds << ":"
       << std::setfill('0') << std::setw(2) << milliseconds;
    timerText.setString(ss.str());
}

void HUD::updateProgress(float passedDistance)
{
    float progress = (passedDistance / totalDistance) * 100.0f;

    if (progress > 100.0f) progress = 100.0f;
    std::stringstream ss;
    ss << "Progress: " << static_cast<int>(progress) << "%";
    progressText.setString(ss.str());
}

void HUD::updateSpeedometer(float currentSpeed)
{
    std::stringstream ss;
    float displaySpeed = currentSpeed / 2.18f;
    ss << "Speed: " << static_cast<int>(displaySpeed) << " km/h";
    speedText.setString(ss.str());
}

void HUD::render(Renderer& renderer)
{
    renderer.render(timerText);
    renderer.render(progressText);
    renderer.render(speedText);
}