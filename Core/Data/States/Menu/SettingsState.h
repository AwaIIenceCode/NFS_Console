//
// Created by AwallencePC on 01.04.2025.
//

#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "../GameState.h"
#include "../../../Application/Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class SettingsState : public GameState
{
public:
    SettingsState(Game* game, sf::Sprite* background);
    ~SettingsState();
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    enum class MenuOption
    {
        CONTROLS,
        SOUND,
        BACK,
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


#endif //SETTINGSSTATE_H
