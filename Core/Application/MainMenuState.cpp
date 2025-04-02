#include "MainMenuState.h"
#include "../Data/States/Menu/GameModeSelectionState.h"
#include "../Data/States/Menu/RecordsModeSelectionState.h"
#include "../Data/States/Menu/SettingsState.h"
#include "../Config/Utils/Logger.h"
#include "Core/Config/Utils/ScaleManager.h"
#include "Core/Data/Managers/Audio/MusicManager.h"

MainMenuState::MainMenuState(Game* game, sf::Sprite* background)
    : GameState(game, true), background(background), selectedOption(MenuOption::START_GAME)
{
    Logger::getInstance().log("MainMenuState created");

    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf"))
    {
        Logger::getInstance().log("Failed to load font for MainMenuState");
    }

    if (!selectSoundBuffer.loadFromFile("J:/MyIDE/NFS_Console/Assets/Sounds/ChangeChoice.wav"))
    {
        Logger::getInstance().log("Failed to load menu select sound");
    }

    selectSound.setBuffer(selectSoundBuffer);

    if (!background->getTexture())
    {
        Logger::getInstance().log("Background texture is missing! Reloading...");
        sf::Texture* backgroundTexture = TextureManager::getInstance().loadTexture("J:/MyIDE/NFS_Console/Assets/Textures/BackgroundMenu.jpg");

        if (backgroundTexture)
        {
            background->setTexture(*backgroundTexture);
            background->setPosition(0.0f, 0.0f);
            ScaleManager::getInstance().scaleSprite(*background);
        }

        else
        {
            Logger::getInstance().log("Failed to reload background texture!");
        }
    }

    initializeMenu();
    MusicManager::getInstance().playMenuMusic();
}

MainMenuState::~MainMenuState()
{
    Logger::getInstance().log("MainMenuState destructor called");
}

void MainMenuState::initializeMenu()
{
    menuItems.resize(static_cast<size_t>(MenuOption::COUNT));

    menuItems[static_cast<size_t>(MenuOption::START_GAME)].setString("Start Game");
    menuItems[static_cast<size_t>(MenuOption::RECORDS)].setString("Records");
    menuItems[static_cast<size_t>(MenuOption::SETTINGS)].setString("Settings");
    menuItems[static_cast<size_t>(MenuOption::EXIT_GAME)].setString("Exit Game");

    for (auto& item : menuItems)
    {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updateMenuPositions();
}

void MainMenuState::updateMenuPositions()
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

void MainMenuState::processEvents(sf::Event& event)
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
                case MenuOption::START_GAME:
                    game->setState(new GameModeSelectionState(game, background));
                    break;

                case MenuOption::RECORDS:
                    game->setState(new RecordsModeSelectionState(game));
                    break;

                case MenuOption::SETTINGS:
                    game->setState(new SettingsState(game, background)); // Переходим в SettingsState
                    break;

                case MenuOption::EXIT_GAME:
                    game->close();
                    break;
            }
        }
    }
}

void MainMenuState::update(float deltaTime)
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

void MainMenuState::render(Renderer& renderer)
{
    renderer.clear(sf::Color::Black);

    if (background->getTexture())
    {
        Logger::getInstance().log("Rendering background in MainMenuState at position: (" +
                                 std::to_string(background->getPosition().x) + ", " +
                                 std::to_string(background->getPosition().y) + ")");
        Logger::getInstance().log("Background scale: (" +
                                 std::to_string(background->getScale().x) + ", " +
                                 std::to_string(background->getScale().y) + ")");
        renderer.render(*background);
    }

    else
    {
        Logger::getInstance().log("Background texture is missing in MainMenuState!");
    }

    for (const auto& item : menuItems)
    {
        renderer.render(item);
    }
    renderer.display();
}