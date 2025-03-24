//
// Created by AwallencePC on 23.03.2025.
//

#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "../Data/States/GameState.h"
#include "Game.h"
#include "../Domain/Entities/PlayerCar.h"
#include "../Config/Settings/GameConfig.h"
#include "../Config/Utils/ScaleManager.h"

class GameplayState : public GameState
{
public:
    GameplayState(Game* game, sf::Sprite* background);
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    sf::Sprite* background;
    PlayerCar playerCar;
};



#endif //GAMEPLAYSTATE_H
