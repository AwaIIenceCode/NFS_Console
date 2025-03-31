// Created by AwallencePC on 30.04.2025.
//

#ifndef NFS_CONSOLE_GAMEOVERSTATE_H
#define NFS_CONSOLE_GAMEOVERSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../GameState.h"
#include "../../../Application/GameMode.h"

class GameOverState : public GameState {
public:
    enum class MenuOption {
        TRY_AGAIN,
        EXIT_MENU,
        COUNT
    };

    GameOverState(Game* game, GameMode mode, float passedDistance);
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    void updateMenuPositions();

    GameMode gameMode;
    float passedDistance;
    MenuOption selectedOption;
    sf::Text gameOverText;
    sf::Text distanceText;
    std::vector<sf::Text> menuItems;
    sf::Font font;
    sf::SoundBuffer selectSoundBuffer;
    sf::Sound selectSound;
};

#endif //NFS_CONSOLE_GAMEOVERSTATE_H