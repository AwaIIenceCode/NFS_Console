#include "GameModeSelectionState.h"
#include <Core/Data/States/Game/GameplayState.h>
#include "../GameState.h"
#include "../../../Config/Utils/Logger.h"
#include "../../../Application/GameMode.h"

GameModeSelectionState::GameModeSelectionState(Game* game, sf::Sprite* background)
    : GameState(game, true), background(background), selectedOption(MenuOption::TIME_TRIAL), modeSelected(false)
{
    Logger::getInstance().log("GameModeSelectionState created");
    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf"))
    {
        Logger::getInstance().log("Failed to load font for GameModeSelectionState");
    }
    ScaleManager::getInstance().scaleSpriteToFill(*background);
    initializeMenu();
}

void GameModeSelectionState::initializeMenu()
{
    menuItems.resize(static_cast<size_t>(MenuOption::COUNT));

    menuItems[static_cast<size_t>(MenuOption::TIME_TRIAL)].setString("Time Trial");
    menuItems[static_cast<size_t>(MenuOption::ENDLESS)].setString("Endless (WIP)");
    menuItems[static_cast<size_t>(MenuOption::RACE)].setString("Race (WIP)");

    for (auto& item : menuItems)
    {
        item.setFont(font);

        if (GameConfig::getInstance().isFullscreen()) { item.setCharacterSize(80); }
        else { item.setCharacterSize(40); }

        item.setFillColor(sf::Color::White);
    }

    updateMenuPositions();
}

void GameModeSelectionState::updateMenuPositions()
{
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 300.0f : 150.0f;
    float rightOffset = GameConfig::getInstance().isFullscreen() ? 800.0f : 300.0f;
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f;

    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        menuItems[i].setPosition(windowWidth - rightOffset, startY + i * verticalSpacing);
    }

    for (auto& item : menuItems)
    {
        if (GameConfig::getInstance().isFullscreen()) { item.setCharacterSize(80); }

        else { item.setCharacterSize(40); }
    }
}

void GameModeSelectionState::processEvents(sf::Event& event)
{
    GameState::processEvents(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (!modeSelected)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                int current = static_cast<int>(selectedOption);
                current = (current - 1 + static_cast<int>(MenuOption::COUNT)) % static_cast<int>(MenuOption::COUNT);
                selectedOption = static_cast<MenuOption>(current);
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                int current = static_cast<int>(selectedOption);
                current = (current + 1) % static_cast<int>(MenuOption::COUNT);
                selectedOption = static_cast<MenuOption>(current);
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                GameMode selectedMode;
                switch (selectedOption)
                {
                    case MenuOption::TIME_TRIAL:
                        selectedMode = GameMode::TIME_TRIAL;
                        break;
                    case MenuOption::ENDLESS:
                        selectedMode = GameMode::ENDLESS;
                        break;
                    case MenuOption::RACE:
                        selectedMode = GameMode::RACE;
                        break;
                    default:
                        selectedMode = GameMode::TIME_TRIAL;
                }
                game->setState(new GameplayState(game, background, selectedMode));
                modeSelected = true;
            }
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            game->setState(new MainMenuState(game, background));
            modeSelected = false;
        }
    }
}

void GameModeSelectionState::update(float deltaTime)
{
    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        if (i == static_cast<size_t>(selectedOption)) { menuItems[i].setFillColor(sf::Color::Yellow); }
        else { menuItems[i].setFillColor(sf::Color::White); }
    }

    updateMenuPositions();
}

void GameModeSelectionState::render(Renderer& renderer)
{
    Logger::getInstance().log("Rendering GameModeSelectionState");
    renderer.clear(sf::Color::Black);
    renderer.render(*background);
    for (const auto& item : menuItems) { renderer.render(item); }
    renderer.display();
}