#include "GameplayState.h"
#include "FinishState.h"
#include "Core/Domain/Entities/Obstacles/Obstacle.h"
#include "Core/Domain/Entities/Bonuses/Lightning.h"
#include "Core/Config/Utils/Logger.h"
#include <fstream>

GameplayState::GameplayState(Game* game, sf::Sprite* background, GameMode mode)
    : GameState(game), background(background), playerCar("Assets/Textures/PurpleCar_1.png"),
      gameMode(mode), timer(), countdown(), hud(25000.0f),
      speedEffectManager(50.0f), speedManager(20.0f, 480.0f, 5.8f),
      audioManager(AudioManager::getInstance()),
      obstacleManager(0.0f, 6.0f,
                      [](float roadLeft, float roadRight) {
                          return std::make_unique<Obstacle>("Assets/Textures/Rock.png", roadLeft, roadRight);
                      },
                      [this](PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed, SpeedController* speedController, std::vector<std::unique_ptr<SpawnableEntity>>& entities) {
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
                                  audioManager.playSound("collision");
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
                       [this](PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed, SpeedController*, std::vector<std::unique_ptr<SpawnableEntity>>& entities) {
                           sf::FloatRect playerBounds = playerCar.getBounds();
                           for (auto it = entities.begin(); it != entities.end();) {
                               sf::FloatRect bounds = (*it)->getBounds();
                               if (playerBounds.intersects(bounds)) {
                                   Logger::getInstance().log("Player picked up a lightning! Applying speed boost.");
                                   speedEffectManager.applyBoost(currentSpeed);
                                   audioManager.playSound("boost");
                                   it = entities.erase(it);
                               } else {
                                   ++it;
                               }
                           }
                       }, this),
      trafficManager(0.0f, 3.0f, // Спавн каждые 3 секунды
                     [](float roadLeft, float roadRight) { // Исправили лямбду
                         static const std::vector<std::string> trafficTextures = {
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_1.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_2.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_3.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_4.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_5.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_6.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_7.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_8.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_9.png",
                             "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_10.png"
                         };
                         int index = rand() % trafficTextures.size();
                         return std::make_unique<TrafficCar>(trafficTextures[index], roadLeft, roadRight);
                     },
                     [](PlayerCar&, SpeedEffectManager&, float&, SpeedController*, std::vector<std::unique_ptr<SpawnableEntity>>&) {
                         // Пока коллизий нет, пустая функция
                     }, nullptr),
      totalDistance(25000.0f), passedDistance(0.0f), raceFinished(false), finishTime(0.0f) {
    Logger::getInstance().log("GameplayState created");

    audioManager.loadSound("engine", "Assets/Sounds/EngineSounds.wav");
    audioManager.loadSound("boost", "Assets/Sounds/LightningSounds.wav");
    audioManager.loadSound("collision", "Assets/Sounds/RockSounds.wav");
    audioManager.playLoopingSound("engine");

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
                                [this](PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed, SpeedController* speedController, std::vector<std::unique_ptr<SpawnableEntity>>& entities) {
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
                                            audioManager.playSound("collision");
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
                                     [this](PlayerCar& playerCar, SpeedEffectManager& speedEffectManager, float& currentSpeed, SpeedController*, std::vector<std::unique_ptr<SpawnableEntity>>& entities) {
                                         sf::FloatRect playerBounds = playerCar.getBounds();
                                         for (auto it = entities.begin(); it != entities.end();) {
                                             sf::FloatRect bounds = (*it)->getBounds();
                                             if (playerBounds.intersects(bounds)) {
                                                 Logger::getInstance().log("Player picked up a lightning! Applying speed boost.");
                                                 speedEffectManager.applyBoost(currentSpeed);
                                                 audioManager.playSound("boost");
                                                 it = entities.erase(it);
                                             } else {
                                                 ++it;
                                             }
                                         }
                                     }, this);
    trafficManager = EntityManager(roadWidth, 3.0f,
                                  [](float roadLeft, float roadRight) { // Исправили лямбду
                                      static const std::vector<std::string> trafficTextures = {
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_1.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_2.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_3.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_4.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_5.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_6.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_7.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_8.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_9.png",
                                          "J:/MyIDE/NFS_Console/Assets/Textures/TrafficCar_10.png"
                                      };
                                      int index = rand() % trafficTextures.size();
                                      return std::make_unique<TrafficCar>(trafficTextures[index], roadLeft, roadRight);
                                  },
                                  [](PlayerCar&, SpeedEffectManager&, float&, SpeedController*, std::vector<std::unique_ptr<SpawnableEntity>>&) {
                                      // Пока коллизий нет
                                  }, nullptr);

    obstacleManager.initialize();
    lightningManager.initialize();
    trafficManager.initialize();
}

GameplayState::~GameplayState() {
    audioManager.stopLoopingSound("engine");
}

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

        float pitch = 0.5f + (currentSpeed - 50.0f) / (450.0f - 50.0f);
        audioManager.setPitch("engine", pitch);

        roadManager.update(deltaTime, currentSpeed, countdown.isCountingDown(), pauseMenuManager.isPaused());
        float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
        float roadLeft = (windowWidth - roadManager.getRoadWidth()) / 2.0f;
        float roadRight = roadLeft + roadManager.getRoadWidth();
        playerCar.update(deltaTime, roadLeft, roadRight);

        passedDistance += currentSpeed * deltaTime;

        hud.updateTimer(timer.getElapsedTime());
        hud.updateProgress(passedDistance);

        sf::FloatRect playerBounds = playerCar.getBounds();
        Logger::getInstance().log("Player bounds before obstacle collision: (left: " + std::to_string(playerBounds.left) +
                                 ", top: " + std::to_string(playerBounds.top) +
                                 ", width: " + std::to_string(playerBounds.width) +
                                 ", height: " + std::to_string(playerBounds.height) + ")");

        obstacleManager.update(deltaTime, currentSpeed, countdown.isCountingDown(), pauseMenuManager.isPaused());
        obstacleManager.checkCollisions(playerCar, speedEffectManager, currentSpeed);

        Logger::getInstance().log("Player bounds before lightning collision: (left: " + std::to_string(playerBounds.left) +
                                 ", top: " + std::to_string(playerBounds.top) +
                                 ", width: " + std::to_string(playerBounds.width) +
                                 ", height: " + std::to_string(playerBounds.height) + ")");

        lightningManager.update(deltaTime, currentSpeed, countdown.isCountingDown(), pauseMenuManager.isPaused());
        lightningManager.checkCollisions(playerCar, speedEffectManager, currentSpeed);

        trafficManager.update(deltaTime, currentSpeed, countdown.isCountingDown(), pauseMenuManager.isPaused());

        speedEffectManager.update(deltaTime, currentSpeed, 420.0f);
        speedManager.setCurrentSpeed(currentSpeed);
        Logger::getInstance().log("Speed after effects: " + std::to_string(currentSpeed));

        hud.updateSpeedometer(currentSpeed);

        if (passedDistance >= totalDistance) {
            raceFinished = true;
            finishTime = timer.getElapsedTime();
            Logger::getInstance().log("Race finished! Time: " + std::to_string(finishTime) + " seconds");
            SaveManager::getInstance().saveRecord(gameMode, finishTime);
            game->setState(new FinishState(game, gameMode, finishTime));
        }
    }

    pauseMenuManager.update(pauseMenuManager.isPaused());
}

void GameplayState::render(Renderer& renderer) {
    roadManager.render(renderer);
    obstacleManager.render(renderer);
    lightningManager.render(renderer);
    trafficManager.render(renderer);
    playerCar.render(renderer);
    countdown.render(renderer);
    hud.render(renderer);
    pauseMenuManager.render(renderer);
}

void GameplayState::resetAcceleration() {
    speedManager.resetAcceleration();
}