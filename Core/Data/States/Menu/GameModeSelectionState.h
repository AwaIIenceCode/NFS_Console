//
// Created by AwallencePC on 24.03.2025.
//

#ifndef GAMEMODESELECTIONSTATE_H
#define GAMEMODESELECTIONSTATE_H

#include "../../../Application/Game.h"
#include "../../../Application/GameMode.h"
#include <vector>

class GameModeSelectionState : public GameState
{
public:
    GameModeSelectionState(Game* game, sf::Sprite* background);
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    enum class MenuOption
    {
        TIME_TRIAL,
        ENDLESS,
        RACE,
        COUNT
    };

    sf::Sprite* background;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    MenuOption selectedOption;
    bool modeSelected;
    void initializeMenu();
    void updateMenuPositions();
};

#endif //GAMEMODESELECTIONSTATE_H