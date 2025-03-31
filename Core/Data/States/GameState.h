//
// Created by AwallencePC on 23.03.2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "../../Domain/Rendering/Renderer.h"
#include "Core/Data/Managers/Audio/MusicManager.h"

class Game;

class GameState {
public:
    GameState(Game* game) : game(game), isMenuState(true) {} // По умолчанию считаем, что это меню
    GameState(Game* game, bool isMenu) : game(game), isMenuState(isMenu) {} // Указываем явно
    virtual ~GameState() = default;
    virtual void processEvents(sf::Event& event) {
        // Добавляем переключение музыки
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::M) { // Следующий трек
                MusicManager::getInstance().nextTrack(isMenuState);
            } else if (event.key.code == sf::Keyboard::N) { // Предыдущий трек
                MusicManager::getInstance().previousTrack(isMenuState);
            }
        }
    }
    virtual void update(float deltaTime) = 0;
    virtual void render(Renderer& renderer) = 0;

protected:
    Game* game;
    bool isMenuState;
};

#endif //GAMESTATE_H
