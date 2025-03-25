// Created by AwallencePC on 23.03.2025.
//

#ifndef NFS_CONSOLE_GAMEPLAYSTATE_H
#define NFS_CONSOLE_GAMEPLAYSTATE_H

#include "GameState.h"
#include "../../Domain/Entities/PlayerCar.h"
#include "../../Domain/Entities/Lightning.h"
#include "../../Config/Settings/GameConfig.h"
#include "../../Application/GameMode.h"
#include "../../Config/Utils/ScaleManager.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <SFML/Audio.hpp>

class GameplayState : public GameState {
public:
    enum class PauseOption {
        RESUME,
        MAIN_MENU,
        COUNT
    };

    GameplayState(Game* game, sf::Sprite* background, GameMode mode);
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    void initializeCountdown();
    void updateCountdown();
    void initializeRoad();
    void updateRoad(float deltaTime);
    void initializePauseMenu();
    void updatePauseMenuPositions();
    void spawnLightning();
    void updateLightnings(float deltaTime);
    void checkLightningCollisions();
    void updateBoost(float deltaTime);
    void updateTimer();
    void updateProgress();

    sf::Sprite* background;
    PlayerCar playerCar;
    GameMode gameMode;
    sf::Sprite road1, road2;
    sf::Texture roadTexture;
    float roadWidth, roadHeight;
    float roadSpeed;
    float baseRoadSpeed;
    float currentRoadSpeed; // Текущая скорость прокрутки дороги
    float initialRoadSpeed; // Начальная скорость
    float accelerationTime; // Время, за которое достигается максимальная скорость
    float totalDistance;
    float passedDistance;
    bool timerStarted;
    sf::Clock gameTimer;
    float finishTime;
    bool raceFinished;
    sf::Text timerText;
    sf::Text progressText;
    sf::Font font;
    bool isCountingDown;
    sf::Text countdownText;
    sf::Clock countdownClock;
    sf::SoundBuffer countdownBuffer;
    sf::Sound countdownSound;
    bool isPaused;
    PauseOption selectedPauseOption;
    sf::Text pauseMessage;
    std::vector<sf::Text> pauseMenuItems;
    sf::SoundBuffer selectSoundBuffer;
    sf::Sound selectSound;
    std::vector<Lightning> lightnings;
    float lightningSpawnInterval;
    sf::Clock lightningSpawnClock;
    bool isBoosted;
    float boostDuration;
    float boostTimer;
    float boostMultiplier;
};

#endif //NFS_CONSOLE_GAMEPLAYSTATE_H