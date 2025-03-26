// Created by AwallencePC on 23.03.2025.
//

#include "GameplayState.h"
#include "FinishState.h"
#include "../../Config/Utils/Logger.h"
#include <fstream>

GameplayState::GameplayState(Game* game, sf::Sprite* background, GameMode mode)
    : GameState(game), background(background), playerCar("Assets/Textures/PurpleCar_1.png"),
      gameMode(mode), timerManager(25000.0f), lightningManager(0.0f), baseRoadSpeed(450.0f),
      currentRoadSpeed(200.0f), initialRoadSpeed(200.0f), accelerationTime(3.6f), passedDistance(0.0f),
      raceFinished(false), finishTime(0.0f) {
    Logger::getInstance().log("GameplayState created");

    playerCar.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f,
                          GameConfig::getInstance().getWindowHeight() * 2.0f / 3.0f);

    roadManager.initialize();
    timerManager.initialize();
    pauseMenuManager.initialize();
    lightningManager.initialize();

    lightningManager = LightningManager(roadManager.getRoadWidth());
}

void GameplayState::processEvents(sf::Event& event)
{
    pauseMenuManager.processEvents(event, game, background, timerManager.isCountingDown(), raceFinished);
}

void GameplayState::update(float deltaTime)
{
    if (timerManager.isCountingDown())
    {
        timerManager.update(deltaTime, passedDistance, pauseMenuManager.isPaused());
    }

    else if (!raceFinished && !pauseMenuManager.isPaused())
    {
        // Обновляем скорость
        if (currentRoadSpeed < baseRoadSpeed)
        {
            float elapsedTime = timerManager.getElapsedTime();
            float speedIncrease = (baseRoadSpeed - initialRoadSpeed) * (elapsedTime / accelerationTime);
            currentRoadSpeed = initialRoadSpeed + speedIncrease;

            if (currentRoadSpeed > baseRoadSpeed)
            {
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
        lightningManager.checkCollisions(playerCar, boostManager, currentRoadSpeed);
        boostManager.update(deltaTime, currentRoadSpeed, baseRoadSpeed);

        if (passedDistance >= 25000.0f)
        {
            raceFinished = true;
            finishTime = timerManager.getElapsedTime();
            Logger::getInstance().log("Race finished! Time: " + std::to_string(finishTime) + " seconds");

            std::ofstream file("records.txt", std::ios::app);
            if (file.is_open())
            {
                std::string modeStr = (gameMode == GameMode::TIME_TRIAL) ? "TimeTrial" : "Unknown";
                file << modeStr << " " << finishTime << "\n";
                file.close();
                Logger::getInstance().log("Result saved: " + modeStr + " " + std::to_string(finishTime));
            }

            else
            {
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
    playerCar.render(renderer);
    timerManager.render(renderer);
    pauseMenuManager.render(renderer);
}