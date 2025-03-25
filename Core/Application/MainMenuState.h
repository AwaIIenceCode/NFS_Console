//
// Created by AwallencePC on 23.03.2025.
//

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../Data/States/GameState.h"
#include "Game.h"
#include "../Config/Settings/GameConfig.h"
#include "../Config/Utils/Logger.h"
#include <vector>
#include <SFML/Audio.hpp>

class MainMenuState : public GameState
{
public:
    MainMenuState(Game* game, sf::Sprite* background);
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    enum class MenuOption
    {
        START_GAME,
        RECORDS,
        SETTINGS,
        EXIT_GAME,
        COUNT // Для подсчёта количества опций
    };

    sf::Sprite* background; // Фон (передаём из Game)
    sf::Font font;
    std::vector<sf::Text> menuItems;
    MenuOption selectedOption;
    sf::SoundBuffer selectSoundBuffer; // Буфер для звука выбора
    sf::Sound selectSound; // Звук выбора

    void initializeMenu();
    void updateMenuPositions(); // Добавляем метод для обновления позиций
};

#endif