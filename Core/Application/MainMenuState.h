//
// Created by AwallencePC on 23.03.2025.
//

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../Data/States/GameState.h"
#include "Game.h"
#include <vector>
#include <SFML/Audio.hpp>

class MainMenuState : public GameState
{
public:
    MainMenuState(Game* game, sf::Sprite* background);
    virtual ~MainMenuState();
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
        COUNT
    };

    sf::Sprite* background;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    MenuOption selectedOption;
    sf::SoundBuffer selectSoundBuffer;
    sf::Sound selectSound;

    void initializeMenu();
    void updateMenuPositions();
};

#endif