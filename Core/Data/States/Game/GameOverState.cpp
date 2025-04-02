// Created by AwallencePC on 30.04.2025.
//

#include "GameOverState.h"
#include "GameplayState.h"
#include "../../../Application/MainMenuState.h"
#include "Core/Config/Settings/GameConfig.h"
#include "Core/Config/Utils/Logger.h"

GameOverState::GameOverState(Game* game, GameMode mode, float passedDistance)
    : GameState(game, true), gameMode(mode), passedDistance(passedDistance), selectedOption(MenuOption::TRY_AGAIN) {
    Logger::getInstance().log("GameOverState created");

    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf"))
    {
        Logger::getInstance().log("Failed to load font for GameOverState!");
    }

    if (!selectSoundBuffer.loadFromFile("J:/MyIDE/NFS_Console/Assets/Sounds/ChangeChoice.wav"))
    {
        Logger::getInstance().log("Failed to load menu select sound in GameOverState");
    }

    selectSound.setBuffer(selectSoundBuffer);

    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, 200.0f);

    distanceText.setFont(font);
    distanceText.setString("Distance: " + std::to_string(static_cast<int>(passedDistance)) + " m");
    distanceText.setCharacterSize(30);
    distanceText.setFillColor(sf::Color::White);
    distanceText.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f - distanceText.getGlobalBounds().width / 2.0f, 300.0f);

    menuItems.resize(static_cast<size_t>(MenuOption::COUNT));
    menuItems[static_cast<size_t>(MenuOption::TRY_AGAIN)].setString("Try Again");
    menuItems[static_cast<size_t>(MenuOption::EXIT_MENU)].setString("Exit Menu");

    for (auto& item : menuItems)
    {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updateMenuPositions();
}

void GameOverState::processEvents(sf::Event& event)
{
    GameState::processEvents(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            int current = static_cast<int>(selectedOption);
            current = (current - 1 + static_cast<int>(MenuOption::COUNT)) % static_cast<int>(MenuOption::COUNT);
            selectedOption = static_cast<MenuOption>(current);
            selectSound.play();
        }

        if (event.key.code == sf::Keyboard::Down)
        {
            int current = static_cast<int>(selectedOption);
            current = (current + 1) % static_cast<int>(MenuOption::COUNT);
            selectedOption = static_cast<MenuOption>(current);
            selectSound.play();
        }

        if (event.key.code == sf::Keyboard::Enter)
        {
            switch (selectedOption)
            {
                case MenuOption::TRY_AGAIN:
                    Logger::getInstance().log("Try Again selected");
                game->setState(new GameplayState(game, new sf::Sprite(), gameMode));
                break;

                case MenuOption::EXIT_MENU:
                    Logger::getInstance().log("Exit Menu selected");
                game->setState(new MainMenuState(game, new sf::Sprite()));
                break;
            }
        }
    }
}

void GameOverState::update(float deltaTime)
{
    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        if (i == static_cast<size_t>(selectedOption))
        {
            menuItems[i].setFillColor(sf::Color::Yellow);
        }

        else
        {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }

    updateMenuPositions();
}

void GameOverState::updateMenuPositions()
{
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = 400.0f;
    float centerX = windowWidth / 2.0f;
    float verticalSpacing = 60.0f;

    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        menuItems[i].setPosition(centerX - menuItems[i].getGlobalBounds().width / 2.0f, startY + i * verticalSpacing);
        menuItems[i].setCharacterSize(30);
    }
}

void GameOverState::render(Renderer& renderer)
{
    renderer.clear(sf::Color::Black);
    renderer.render(gameOverText);
    renderer.render(distanceText);

    for (const auto& item : menuItems)
    {
        renderer.render(item);
    }

    renderer.display();
}