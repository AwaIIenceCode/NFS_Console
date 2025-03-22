//
// Created by AwallencePC on 18.03.2025.
// Game: Главный класс игры, управляет игровым циклом, состояниями и событиями.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    void processEvents();
    void update();
    void render();
};



#endif //GAME_H
