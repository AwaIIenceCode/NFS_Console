//
// Created by AwallencePC on 23.03.2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "../Domain/Rendering/Renderer.h"

class Game;

class GameState
{
public:
    virtual ~GameState() = default;
    virtual void processEvents(sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer& renderer) = 0;

protected:
    Game* game; // Указатель на Game для управления состояниями
    GameState(Game* game) : game(game) {}
};

#endif //GAMESTATE_H
