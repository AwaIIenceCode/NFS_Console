//
// Created by AwallencePC on 19.03.2025.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../Config/Settings/GameConfig.h"
#include "../Config/Utils/Logger.h"
#include "../Config/Utils/ScaleManager.h"
#include "../Domain/Rendering/Renderer.h"
#include "../Domain/Rendering/TextureManager.h"

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow window;
    Renderer renderer;
    sf::Sprite background;
    void processEvents();
    void update();
    void render();
    void updateWindowSettings(); // Новый метод для обновления настроек окна
};

#endif