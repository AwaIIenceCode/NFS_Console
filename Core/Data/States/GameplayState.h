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
#include "../Managers/BoostManager.h"

class GameplayState : public GameState
{
public:
    GameplayState(Game* game, sf::Sprite* background, GameMode mode);
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    sf::Sprite* background;
    PlayerCar playerCar;
    GameMode gameMode;
    RoadManager roadManager;
    TimerManager timerManager;
    PauseMenuManager pauseMenuManager;
    LightningManager lightningManager;
    BoostManager boostManager;

    float baseRoadSpeed;
    float currentRoadSpeed;
    float initialRoadSpeed;
    float accelerationTime;
    float passedDistance;
    bool raceFinished;
    float finishTime;
};

#endif //NFS_CONSOLE_GAMEPLAYSTATE_H