// Created by AwallencePC on 23.03.2025.
//

#ifndef NFS_CONSOLE_GAMEPLAYSTATE_H
#define NFS_CONSOLE_GAMEPLAYSTATE_H

#include "GameState.h"
#include "../../Application/GameMode.h"
#include "../../Domain/Entities/PlayerCar.h"
#include "../Managers/RoadManager.h"
#include "../Managers/Timer.h"
#include "../Managers/Countdown.h"
#include "../Managers/HUD.h"
#include "../Managers/PauseMenuManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/SpeedEffectManager.h"
#include "../Managers/SpeedManager.h"
#include "../../Data/Managers/Interfaces/SpeedController.h"

class GameplayState : public GameState, public SpeedController {
public:
    GameplayState(Game* game, sf::Sprite* background, GameMode mode);
    virtual ~GameplayState();
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;
    void resetAcceleration() override;

private:
    sf::Sprite* background;
    PlayerCar playerCar;
    GameMode gameMode;
    RoadManager roadManager;
    Timer timer;
    Countdown countdown;
    HUD hud;
    PauseMenuManager pauseMenuManager;
    EntityManager obstacleManager;
    EntityManager lightningManager;
    SpeedEffectManager speedEffectManager;
    SpeedManager speedManager;

    float totalDistance;
    float passedDistance;
    bool raceFinished;
    float finishTime;
};

#endif //NFS_CONSOLE_GAMEPLAYSTATE_H