// Created by AwallencePC on 23.03.2025.
//

#include "GameplayState.h"
#include "FinishState.h"
#include "../../Domain/Entities/Obstacle.h"
#include "../../Domain/Entities/Lightning.h"
#include "../../Config/Utils/Logger.h"
#include <fstream>

GameplayState::GameplayState(Game* game, sf::Sprite* background, GameMode mode)
    : GameState(game), background(background), playerCar("Assets/Textures/PurpleCar_1.png"),
      gameMode(mode), timer(), countdown(), hud(25000.0f),
      speedEffectManager(50.0f), speedManager(50.0f, 450.0f, 3.8f),
      obstacleManager(0.0f, 6.0f,
                      [](float roadLeft, float roadRight) {
                          return std::make_unique<Obstacle>("Assets/Textures/Rock.png", roadLeft, roadRight);
                      },
                      [](PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed, SpeedController* speedController, std::vector<std::unique_ptr<SpawnableEntity>>& entities) {
                          sf::FloatRect playerBounds = playerCar.getBounds();
                          for (auto it = entities.begin(); it != entities.end();) {
                              sf::FloatRect bounds = (*it)->getBounds();
                              if (playerBounds.intersects(bounds)) {
                                  Logger::getInstance().log("Player hit an obstacle! Applying speed reduction.");
                                  speedEffectManager.applySlowdown(currentSpeed);
                                  speedController->resetAcceleration();
                                  it = entities.erase(it);
                              } else {
                                  ++it;
                              }
                          }
                      }, this),
      lightningManager(0.0f, 10.0f,
                       [](float roadLeft, float roadRight) {
                           return std::make_unique<Lightning>("Assets/Textures/Lightning.png", roadLeft, roadRight);
                       },
                       [](PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed, SpeedController*, std::vector<std::unique_ptr<SpawnableEntity>>& entities) {
                           sf::FloatRect playerBounds = playerCar.getBounds();
                           for (auto it = entities.begin(); it != entities.end();) {
                               sf::FloatRect bounds = (*it)->getBounds();
                               if (playerBounds.intersects(bounds)) {
                                   Logger::getInstance().log("Player picked up a lightning! Applying speed boost.");
                                   speedEffectManager.applyBoost(currentSpeed);
                                   it = entities.erase(it);
                               } else {
                                   ++it;
                               }
                           }
                       }, this),
      totalDistance(25000.0f), passedDistance(0.0f), raceFinished(false), finishTime(0.0f) {
    Logger::getInstance().log("GameplayState created");

    float initialY = GameConfig::getInstance().getWindowHeight() * 2.0f / 3.0f + 100.0f;
    playerCar.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f, initialY);

    roadManager.initialize();
    countdown.initialize();
    hud.initialize();
    pauseMenuManager.initialize();

    float roadWidth = roadManager.getRoadWidth();
    obstacleManager = EntityManager(roadWidth, 6.0f,
                                [](float roadLeft, float roadRight) {
                                    return std::make_unique<Obstacle>("Assets/Textures/Rock.png", roadLeft, roadRight);
                                },
                                [](PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed, SpeedController* speedController, std::vector<std::unique_ptr<SpawnableEntity>>& entities) {
                                    sf::FloatRect playerBounds = playerCar.getBounds();
                                    for (auto it = entities.begin(); it != entities.end();) {
                                        sf::FloatRect bounds = (*it)->getBounds();
                                        Logger::getInstance().log("Obstacle bounds: (left: " + std::to_string(bounds.left) +
                                                                 ", top: " + std::to_string(bounds.top) +
                                                                 ", width: " + std::to_string(bounds.width) +
                                                                 ", height: " + std::to_string(bounds.height) + ")");
                                        if (playerBounds.intersects(bounds)) {
                                            Logger::getInstance().log("Player hit an obstacle! Applying speed reduction.");
                                            speedEffectManager.applySlowdown(currentSpeed);
                                            speedController->resetAcceleration();
                                            it = entities.erase(it);
                                        } else {
                                            ++it;
                                        }
                                    }
                                }, this);
    lightningManager = EntityManager(roadWidth, 10.0f,
                                     [](float roadLeft, float roadRight) {
                                         return std::make_unique<Lightning>("Assets/Textures/Lightning.png", roadLeft, roadRight);
                                     },
                                     [](PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed, SpeedController*, std::vector<std::unique_ptr<SpawnableEntity>>& entities) {
                                         sf::FloatRect playerBounds = playerCar.getBounds();
                                         for (auto it = entities.begin(); it != entities.end();) {
                                             sf::FloatRect bounds = (*it)->getBounds();
                                             if (playerBounds.intersects(bounds)) {
                                                 Logger::getInstance().log("Player picked up a lightning! Applying speed boost.");
                                                 speedEffectManager.applyBoost(currentSpeed);
                                                 it = entities.erase(it);
                                             } else {
                                                 ++it;
                                             }
                                         }
                                     }, this);
    obstacleManager.initialize();
    lightningManager.initialize();
}

GameplayState::~GameplayState() {}

void GameplayState::processEvents(sf::Event& event) {
    pauseMenuManager.processEvents(event, game, background, countdown.isCountingDown(), raceFinished);
}

void GameplayState::update(float deltaTime) {
    if (countdown.isCountingDown()) {
        countdown.update(deltaTime);
        if (!countdown.isCountingDown() && !timer.isStarted()) {
            timer.start();
        }
    } else if (!raceFinished && !pauseMenuManager.isPaused()) {
        static bool accelerationStarted = false;
        if (!accelerationStarted) {
            speedManager.resetAcceleration();
            accelerationStarted = true;
        }

        speedManager.update(deltaTime);
        float currentSpeed = speedManager.getCurrentSpeed();
        Logger::getInstance().log("Speed before effects: " + std::to_string(currentSpeed));

        roadManager.update(deltaTime, currentSpeed, countdown.isCountingDown(), pauseMenuManager.isPaused());
        float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
        float roadLeft = (windowWidth - roadManager.getRoadWidth()) / 2.0f;
        float roadRight = roadLeft + roadManager.getRoadWidth();
        playerCar.update(deltaTime, roadLeft, roadRight);

        passedDistance += currentSpeed * deltaTime;

        hud.updateTimer(timer.getElapsedTime());
        hud.updateProgress(passedDistance);

        // Логируем границы игрока перед проверкой столкновений с камнями
        sf::FloatRect playerBounds = playerCar.getBounds();
        Logger::getInstance().log("Player bounds before obstacle collision: (left: " + std::to_string(playerBounds.left) +
                                 ", top: " + std::to_string(playerBounds.top) +
                                 ", width: " + std::to_string(playerBounds.width) +
                                 ", height: " + std::to_string(playerBounds.height) + ")");

        obstacleManager.update(deltaTime, currentSpeed, countdown.isCountingDown(), pauseMenuManager.isPaused());
        obstacleManager.checkCollisions(playerCar, speedEffectManager, currentSpeed);

        // Логируем границы игрока перед проверкой столкновений с молнией
        Logger::getInstance().log("Player bounds before lightning collision: (left: " + std::to_string(playerBounds.left) +
                                 ", top: " + std::to_string(playerBounds.top) +
                                 ", width: " + std::to_string(playerBounds.width) +
                                 ", height: " + std::to_string(playerBounds.height) + ")");

        lightningManager.update(deltaTime, currentSpeed, countdown.isCountingDown(), pauseMenuManager.isPaused());
        lightningManager.checkCollisions(playerCar, speedEffectManager, currentSpeed);
        speedEffectManager.update(deltaTime, currentSpeed, 420.0f);

        // Синхронизируем скорость с SpeedManager после применения эффектов
        speedManager.setCurrentSpeed(currentSpeed);
        Logger::getInstance().log("Speed after effects: " + std::to_string(currentSpeed));

        hud.updateSpeedometer(currentSpeed);

        if (passedDistance >= totalDistance) {
            raceFinished = true;
            finishTime = timer.getElapsedTime();
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
    obstacleManager.render(renderer);
    lightningManager.render(renderer);
    playerCar.render(renderer);
    countdown.render(renderer);
    hud.render(renderer);
    pauseMenuManager.render(renderer);
}

void GameplayState::resetAcceleration() {
    speedManager.resetAcceleration();
}