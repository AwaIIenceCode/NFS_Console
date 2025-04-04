#ifndef NFS_CONSOLE_GAMEPLAYSTATE_H
#define NFS_CONSOLE_GAMEPLAYSTATE_H

#include "../../../Data/Managers/Utility/SaveManager.h"
#include "../GameState.h"
#include "../../../Application/GameMode.h"
#include "../../../Domain/Entities/Cars/PlayerCar.h"
#include "../../../Domain/Entities/Cars/TrafficCar.h"
#include "../../Managers/Gameplay/RoadManager.h"
#include "../../Managers/Utility/Timer.h"
#include "../../Managers/Utility/TimerManager.h"
#include "../../Managers/UI/HUD.h"
#include "../../Managers/UI/PauseMenuManager.h"
#include "../../Managers/../Managers/Gameplay/EntityManager.h"
#include "../../Managers/Gameplay/SpeedEffectManager.h"
#include "../../Managers/Gameplay/SpeedManager.h"
#include "../../../../Core/Data/Managers/Audio/AudioManager.h"
#include "../../../Data/Managers/Interfaces/SpeedController.h"
#include "Core/Data/States/Game/GameOverState.h"

class GameplayState : public GameState, public SpeedController
{
public:
    GameplayState(Game* game, sf::Sprite* background, GameMode mode);
    virtual ~GameplayState();
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;
    void resetAcceleration() override;
    void updatePositions();

private:
    sf::Sprite* background;
    PlayerCar playerCar;
    GameMode gameMode;
    RoadManager roadManager;
    Timer timer;
    TimerManager timerManager;
    HUD hud;
    PauseMenuManager pauseMenuManager;
    EntityManager obstacleManager;
    EntityManager lightningManager;
    EntityManager trafficManager;
    SpeedEffectManager speedEffectManager;
    SpeedManager speedManager;
    AudioManager& audioManager;

    float totalDistance;
    float passedDistance;
    bool raceFinished;
    float finishTime;
    float trafficSpawnDelayTimer;
};

#endif //NFS_CONSOLE_GAMEPLAYSTATE_H