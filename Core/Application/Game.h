//
//Created by AwallencePC on 19.03.2025.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../Data/States/GameState.h"
#include "MainMenuState.h"
#include "../Config/Utils/Logger.h"
#include "../Domain/Rendering/Renderer.h"
#include "../Domain/Rendering/TextureManager.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
    void setState(GameState* newState);
    void close();
    sf::Sprite* getBackground();
    sf::Sprite* getRecordsBackground();

private:
    sf::RenderWindow window;
    Renderer renderer;
    sf::Sprite background;
    sf::Sprite recordsBackground;
    GameState* currentState;
    sf::Clock clock;
    void processEvents();
    void update(float deltaTime);
    void render();
    void updateWindowSettings();
};

#endif //GAME_H