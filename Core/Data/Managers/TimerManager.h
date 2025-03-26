// Created by AwallencePC on 26.03.2025.
//

#ifndef NFS_CONSOLE_TIMERMANAGER_H
#define NFS_CONSOLE_TIMERMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../Domain/Rendering/Renderer.h"

class TimerManager {
public:
    TimerManager(float totalDistance);
    void initialize();
    void update(float deltaTime, float passedDistance, bool isPaused);
    void render(Renderer& renderer);
    void updateSpeedometer(float currentSpeed);

    bool isCountingDown() const { return isCountingDownFlag; }
    bool isTimerStarted() const { return timerStarted; }
    void startTimer() { timerStarted = true; gameTimer.restart(); }
    float getElapsedTime() const { return gameTimer.getElapsedTime().asSeconds(); }

private:
    void updateCountdown();
    void updateTimer();
    void updateProgress(float passedDistance);

    float totalDistance;
    float passedDistance;
    bool timerStarted;
    sf::Clock gameTimer;
    sf::Text timerText;
    sf::Text progressText;
    sf::Text speedText;
    sf::Font font;
    bool isCountingDownFlag;
    sf::Text countdownText;
    sf::Clock countdownClock;
    sf::SoundBuffer countdownBuffer;
    sf::Sound countdownSound;
};

#endif //NFS_CONSOLE_TIMERMANAGER_H