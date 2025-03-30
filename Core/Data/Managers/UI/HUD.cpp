// Created by AwallencePC on 27.03.2025.
//

#include "HUD.h"
#include <sstream>
#include <iomanip>

HUD::HUD(float totalDistance) : totalDistance(totalDistance) {}

void HUD::initialize() {
    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for HUD");
    }

    timerText.setFont(font);
    timerText.setCharacterSize(40);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(20.0f, 20.0f);

    progressText.setFont(font);
    progressText.setCharacterSize(40);
    progressText.setFillColor(sf::Color::White);
    progressText.setPosition(20.0f, 70.0f);

    speedText.setFont(font);
    speedText.setCharacterSize(40);
    speedText.setFillColor(sf::Color::White);
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    speedText.setPosition(windowWidth - 350.0f, 30.0f);
    speedText.setString("Speed: 0 km/h");
}

void HUD::updateTimer(float elapsedTime) {
    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;
    int milliseconds = static_cast<int>(elapsedTime * 1000) % 1000 / 10;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds << ":"
       << std::setfill('0') << std::setw(2) << milliseconds;
    timerText.setString(ss.str());
}

void HUD::updateProgress(float passedDistance) {
    float progress = (passedDistance / totalDistance) * 100.0f;
    if (progress > 100.0f) progress = 100.0f;
    std::stringstream ss;
    ss << "Progress: " << static_cast<int>(progress) << "%";
    progressText.setString(ss.str());
}

void HUD::updateSpeedometer(float currentSpeed) {
    std::stringstream ss;
    float displaySpeed = currentSpeed / 2.18f;
    ss << "Speed: " << static_cast<int>(displaySpeed) << " km/h";
    speedText.setString(ss.str());
}

void HUD::render(Renderer& renderer) {
    renderer.render(timerText);
    renderer.render(progressText);
    renderer.render(speedText);
}