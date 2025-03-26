// Created by AwallencePC on 23.03.2025.
//

#include "GameplayState.h"
#include "FinishState.h"
#include "../Managers/ObstacleManager.h"
#include "../../Config/Utils/Logger.h"
#include <fstream>

GameplayState::GameplayState(Game* game, sf::Sprite* background, GameMode mode)
    : GameState(game), background(background), playerCar("Assets/Textures/PurpleCar_1.png"),
      gameMode(mode), timerManager(25000.0f), lightningManager(0.0f), obstacleManager(nullptr),
      speedEffectManager(50.0f),
      baseRoadSpeed(420.0f), currentRoadSpeed(50.0f), initialRoadSpeed(50.0f), accelerationTime(3.8f),
      passedDistance(0.0f), raceFinished(false), finishTime(0.0f) {
    Logger::getInstance().log("GameplayState created");

    // Сдвигаем машинку ниже на 100 пикселей (примерно корпус)
    float initialY = GameConfig::getInstance().getWindowHeight() * 2.0f / 3.0f + 100.0f;
    playerCar.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f, initialY);

    roadManager.initialize();
    timerManager.initialize();
    pauseMenuManager.initialize();
    lightningManager.initialize();

    // Инициализируем obstacleManager
    obstacleManager = new ObstacleManager(0.0f, this);
    obstacleManager->initialize();

    lightningManager = LightningManager(roadManager.getRoadWidth());
    obstacleManager = new ObstacleManager(roadManager.getRoadWidth(), this);
}

GameplayState::~GameplayState() {
    delete obstacleManager; // Освобождаем память
}

void GameplayState::processEvents(sf::Event& event) {
    pauseMenuManager.processEvents(event, game, background, timerManager.isCountingDown(), raceFinished);
}

void GameplayState::update(float deltaTime) {
    if (timerManager.isCountingDown()) {
        timerManager.update(deltaTime, passedDistance, pauseMenuManager.isPaused());
    } else if (!raceFinished && !pauseMenuManager.isPaused()) {
        // Запускаем accelerationTimer, если он ещё не запущен
        static bool accelerationTimerStarted = false;
        if (!accelerationTimerStarted) {
            accelerationTimer.restart();
            accelerationTimerStarted = true;
        }

        // Обновляем скорость
        if (currentRoadSpeed < baseRoadSpeed) {
            float elapsedTime = accelerationTimer.getElapsedTime().asSeconds();
            float speedIncrease = (baseRoadSpeed - initialRoadSpeed) * (elapsedTime / accelerationTime);
            currentRoadSpeed = initialRoadSpeed + speedIncrease;
            if (currentRoadSpeed > baseRoadSpeed) {
                currentRoadSpeed = baseRoadSpeed;
            }
        }

        roadManager.update(deltaTime, currentRoadSpeed, timerManager.isCountingDown(), pauseMenuManager.isPaused());
        float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
        float roadLeft = (windowWidth - roadManager.getRoadWidth()) / 2.0f;
        float roadRight = roadLeft + roadManager.getRoadWidth();
        playerCar.update(deltaTime, roadLeft, roadRight);

        passedDistance += currentRoadSpeed * deltaTime;

        timerManager.update(deltaTime, passedDistance, pauseMenuManager.isPaused());
        lightningManager.update(deltaTime, currentRoadSpeed, timerManager.isCountingDown(), pauseMenuManager.isPaused());
        lightningManager.checkCollisions(playerCar, speedEffectManager, currentRoadSpeed);
        obstacleManager->update(deltaTime, currentRoadSpeed, timerManager.isCountingDown(), pauseMenuManager.isPaused());
        obstacleManager->checkCollisions(playerCar, speedEffectManager, currentRoadSpeed);
        speedEffectManager.update(deltaTime, currentRoadSpeed, baseRoadSpeed);

        // Обновляем спидометр после всех изменений скорости
        timerManager.updateSpeedometer(currentRoadSpeed);

        if (passedDistance >= 25000.0f) {
            raceFinished = true;
            finishTime = timerManager.getElapsedTime();
            Logger::getInstance().log("Race finished! Time: " + std::to_string(finishTime) + " seconds");

            std::ofstream file("records.txt", std::ios::app);
            if (file.is_open()) {
                std::string modeStr = (gameMode == GameMode::TIME_TRIAL) ? "TimeTrial" : "Unknown";
                file << modeStr << " " << finishTime << "\n";
                file.close();
                Logger::getInstance().log("Result saved: " + modeStr + " " + std::to_string(finishTime));
            } else {
                Logger::getInstance().log("Failed to open records.txt for saving");
            }

            game->setState(new FinishState(game, gameMode, finishTime));
        }
    }

    pauseMenuManager.update(pauseMenuManager.isPaused());
}

void GameplayState::render(Renderer& renderer) {
    roadManager.render(renderer);
    lightningManager.render(renderer);
    obstacleManager->render(renderer);
    playerCar.render(renderer);
    timerManager.render(renderer);
    pauseMenuManager.render(renderer);
}

void GameplayState::resetAcceleration()
{
    currentRoadSpeed = initialRoadSpeed;
    accelerationTimer.restart();
    Logger::getInstance().log("Acceleration reset. Speed set to " + std::to_string(currentRoadSpeed));
}