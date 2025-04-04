//
// Created by AwallencePC on 26.03.2025.
//

#include "PauseMenuManager.h"
#include "../../../Application/MainMenuState.h"
#include "../../States/GameState.h"
#include "Core/Config/Settings/GameConfig.h"

PauseMenuManager::PauseMenuManager() : isPausedFlag(false), selectedPauseOption(PauseOption::RESUME) {}

void PauseMenuManager::initialize()
{
    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf"))
    {
        Logger::getInstance().log("Failed to load font for PauseMenuManager");
    }

    if (!selectSoundBuffer.loadFromFile("J:/MyIDE/NFS_Console/Assets/Sounds/ChangeChoice.wav"))
    {
        Logger::getInstance().log("Failed to load menu select sound");
    }

    selectSound.setBuffer(selectSoundBuffer);

    pauseMessage.setFont(font);
    pauseMessage.setFillColor(sf::Color::White);
    pauseMessage.setString("Paused");

    pauseMenuItems.resize(static_cast<size_t>(PauseOption::COUNT));
    pauseMenuItems[static_cast<size_t>(PauseOption::RESUME)].setString("Resume");
    pauseMenuItems[static_cast<size_t>(PauseOption::MAIN_MENU)].setString("Main Menu");

    for (auto& item : pauseMenuItems)
    {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updatePauseMenuPositions();
}

void PauseMenuManager::processEvents(sf::Event& event, Game* game, sf::Sprite* background, bool isCountingDown, bool raceFinished)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape && !isCountingDown && !raceFinished)
        {
            isPausedFlag = !isPausedFlag;
        }

        if (isPausedFlag)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                int current = static_cast<int>(selectedPauseOption);
                current = (current - 1 + static_cast<int>(PauseOption::COUNT)) % static_cast<int>(PauseOption::COUNT);
                selectedPauseOption = static_cast<PauseOption>(current);
                selectSound.play();
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                int current = static_cast<int>(selectedPauseOption);
                current = (current + 1) % static_cast<int>(PauseOption::COUNT);
                selectedPauseOption = static_cast<PauseOption>(current);
                selectSound.play();
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                switch (selectedPauseOption)
                {
                    case PauseOption::RESUME:
                        isPausedFlag = false;
                        break;

                    case PauseOption::MAIN_MENU:
                        game->setState(new MainMenuState(game, background));
                        break;
                }
            }
        }
    }
}

void PauseMenuManager::update(bool isPaused)
{
    if (isPaused)
    {
        for (size_t i = 0; i < pauseMenuItems.size(); ++i)
        {
            if (i == static_cast<size_t>(selectedPauseOption)) { pauseMenuItems[i].setFillColor(sf::Color::Yellow); }

            else { pauseMenuItems[i].setFillColor(sf::Color::White); }
        }

        updatePauseMenuPositions();
    }
}

void PauseMenuManager::updatePauseMenuPositions()
{
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float windowHeight = static_cast<float>(GameConfig::getInstance().getWindowHeight());

    float rightOffset = windowWidth * 0.25f;
    float startY = windowHeight * 0.2f;
    float verticalSpacing = windowHeight * 0.1f;
    float baseFontSize = windowHeight * 0.05f;
    float messageFontSize = windowHeight * 0.07f;

    pauseMessage.setPosition(windowWidth - rightOffset, startY);
    for (size_t i = 0; i < pauseMenuItems.size(); ++i)
    {
        pauseMenuItems[i].setPosition(windowWidth - rightOffset, startY + (1 + i) * verticalSpacing);
    }

    pauseMessage.setCharacterSize(static_cast<unsigned int>(messageFontSize));

    for (auto& item : pauseMenuItems)
    {
        item.setCharacterSize(static_cast<unsigned int>(baseFontSize));
    }
}

void PauseMenuManager::render(Renderer& renderer)
{
    if (isPausedFlag)
    {
        renderer.render(pauseMessage);

        for (const auto& item : pauseMenuItems) { renderer.render(item); }
    }
}