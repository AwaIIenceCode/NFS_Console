//
// Created by AwallencePC on 26.03.2025.
//

#ifndef NFS_CONSOLE_PAUSEMENUMANAGER_H
#define NFS_CONSOLE_PAUSEMENUMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../States/GameState.h"

class PauseMenuManager
{
public:
    enum class PauseOption
    {
        RESUME,
        MAIN_MENU,
        COUNT
    };

    PauseMenuManager();
    void initialize();
    void processEvents(sf::Event& event, Game* game, sf::Sprite* background, bool isCountingDown, bool raceFinished);
    void update(bool isPaused);
    void render(Renderer& renderer);

    bool isPaused() const { return isPausedFlag; }

private:
    void updatePauseMenuPositions();

    bool isPausedFlag;
    PauseOption selectedPauseOption;
    sf::Text pauseMessage;
    std::vector<sf::Text> pauseMenuItems;
    sf::Font font;
    sf::SoundBuffer selectSoundBuffer;
    sf::Sound selectSound;
};

#endif //NFS_CONSOLE_PAUSEMENUMANAGER_H