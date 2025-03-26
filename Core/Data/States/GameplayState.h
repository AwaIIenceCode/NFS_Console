// Created by AwallencePC on 23.03.2025.
//

#ifndef NFS_CONSOLE_GAMEPLAYSTATE_H
#define NFS_CONSOLE_GAMEPLAYSTATE_H

#include "GameState.h"
#include "../../Application/GameMode.h"
#include "../../Domain/Entities/PlayerCar.h"
#include "../Managers/RoadManager.h"
#include "../Managers/TimerManager.h"
#include "../Managers/PauseMenuManager.h"
#include "../Managers/LightningManager.h"
#include "../Managers/SpeedEffectManager.h"

// Предварительное объявление класса ObstacleManager
class ObstacleManager;

class GameplayState : public GameState {
public:
    GameplayState(Game* game, sf::Sprite* background, GameMode mode);
    virtual ~GameplayState();
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;
    void resetAcceleration();

private:
    sf::Sprite* background;
    PlayerCar playerCar;
    GameMode gameMode;
    RoadManager roadManager;
    TimerManager timerManager;
    PauseMenuManager pauseMenuManager;
    LightningManager lightningManager;
    SpeedEffectManager speedEffectManager;
    ObstacleManager* obstacleManager;

    float baseRoadSpeed;
    float currentRoadSpeed;
    float initialRoadSpeed;
    float accelerationTime;
    float passedDistance;
    bool raceFinished;
    float finishTime;
    sf::Clock accelerationTimer; // Добавляем таймер для ускорения
};

#endif //NFS_CONSOLE_GAMEPLAYSTATE_H