//
// Created by AwallencePC on 18.03.2025.
// Game: Главный класс игры, управляет игровым циклом, состояниями и событиями.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../Config/Settings/GameConfig.h"
#include "../Config/Utils/Logger.h"
#include "../../Core/Domain/Rendering/Renderer.h"
#include "../../Core/Domain/Rendering/TextureManager.h"

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow window;
    void processEvents();
    Renderer renderer;
    sf::Sprite background; // Спрайт для фона
    void update();
    void render();
};



#endif //GAME_H
