//
// Created by AwallencePC on 25.03.2025.
//

#ifndef FINISHSTATE_H
#define FINISHSTATE_H

#include "../GameState.h"
#include "../../../Application/Game.h"
#include "../../../Application/GameMode.h"
#include <SFML/Graphics.hpp>
#include <vector>

class FinishState : public GameState
{
public:
    FinishState(Game* game, GameMode mode, float finishTime);
    ~FinishState();
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    enum class MenuOption {
        RESTART,
        MAIN_MENU,
        COUNT
    };

    sf::Sprite* background;
    sf::Font font;
    sf::Text finishMessage;
    sf::Text timeText;
    sf::Text medalText;
    std::vector<sf::Text> menuItems;
    MenuOption selectedOption;
    sf::SoundBuffer selectSoundBuffer;
    sf::Sound selectSound;
    GameMode mode;
    float finishTime;

    void initializeMenu();
    void updateMenuPositions();
    void determineMedal();
};

#endif //FINISHSTATE_H