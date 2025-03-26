// Created by AwallencePC on 26.03.2025.
//

#include "TimerManager.h"
#include "../../Config/Settings/GameConfig.h"
#include "../../Config/Utils/Logger.h"
#include <sstream>
#include <iomanip>

TimerManager::TimerManager(float totalDistance)
    : totalDistance(totalDistance), passedDistance(0.0f), timerStarted(false), isCountingDownFlag(true) {}

void TimerManager::initialize() {
    if (!font.loadFromFile("Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for TimerManager");
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
    // Перемещаем спидометр в правую сторону окна
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    speedText.setPosition(windowWidth - 350.0f, 30.0f);
    speedText.setString("Speed: 0 km/h");

    countdownText.setFont(font);
    countdownText.setCharacterSize(100);
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f - 50.0f,
                             GameConfig::getInstance().getWindowHeight() / 2.0f - 50.0f);
    countdownText.setString("3");

    if (!countdownBuffer.loadFromFile("Assets/Sounds/StartSound_1.wav")) {
        Logger::getInstance().log("Failed to load countdown sound");
    }

    countdownSound.setBuffer(countdownBuffer);
    countdownSound.play();
}

void TimerManager::update(float deltaTime, float passedDistance, bool isPaused) {
    this->passedDistance = passedDistance;

    if (isCountingDownFlag) {
        updateCountdown();
        if (!isCountingDownFlag && !timerStarted) { startTimer(); }
    } else if (!isPaused) {
        updateTimer();
        updateProgress(passedDistance);
    }
}

void TimerManager::updateCountdown() {
    float elapsed = countdownClock.getElapsedTime().asSeconds();
    if (elapsed < 1.0f) { countdownText.setString("3"); }
    else if (elapsed < 2.0f) { countdownText.setString("2"); }
    else if (elapsed < 3.0f) { countdownText.setString("1"); }
    else if (elapsed < 4.0f) { countdownText.setString("Go!"); }
    else { isCountingDownFlag = false; }
}

void TimerManager::updateTimer() {
    if (timerStarted) {
        sf::Time elapsed = gameTimer.getElapsedTime();
        int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
        int milliseconds = static_cast<int>(elapsed.asMilliseconds()) % 1000 / 10;

        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << minutes << ":"
           << std::setfill('0') << std::setw(2) << seconds << ":"
           << std::setfill('0') << std::setw(2) << milliseconds;
        timerText.setString(ss.str());
    }
}

void TimerManager::updateProgress(float passedDistance) {
    float progress = (passedDistance / totalDistance) * 100.0f;
    if (progress > 100.0f) progress = 100.0f;
    std::stringstream ss;
    ss << "Progress: " << static_cast<int>(progress) << "%";
    progressText.setString(ss.str());
}

void TimerManager::updateSpeedometer(float currentSpeed) {
    std::stringstream ss;
    float displaySpeed = currentSpeed / 2.18f;
    ss << "Speed: " << static_cast<int>(displaySpeed) << " km/h";
    speedText.setString(ss.str());
}

void TimerManager::render(Renderer& renderer) {
    if (isCountingDownFlag) { renderer.render(countdownText); }
    renderer.render(timerText);
    renderer.render(progressText);
    renderer.render(speedText);
}