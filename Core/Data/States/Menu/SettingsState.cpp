#include "SettingsState.h"
#include "../../../Application/MainMenuState.h"
#include "../../../Config/Utils/Logger.h"
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Data/Managers/Audio/MusicManager.h"
#include "Core/Config/Utils/ScaleManager.h"

SettingsState::SettingsState(Game* game, sf::Sprite* background)
    : GameState(game, true), background(background), selectedOption(MenuOption::FULLSCREEN) {
    Logger::getInstance().log("SettingsState created");

    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf"))
    {
        Logger::getInstance().log("Failed to load font for SettingsState");
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
            ScaleManager::getInstance().scaleSpriteToFill(*background);
        }
        else
        {
            Logger::getInstance().log("Failed to reload background texture!");
        }
    }
    else
    {
        ScaleManager::getInstance().scaleSpriteToFill(*background);
    }

    // Синхронизируем громкость из GameConfig с MusicManager
    float volume = GameConfig::getInstance().getMusicVolume();
    MusicManager::getInstance().setVolume(volume);

    initializeMenu();
    MusicManager::getInstance().playMenuMusic();
}

SettingsState::~SettingsState()
{
    Logger::getInstance().log("SettingsState destructor called");
}

void SettingsState::initializeMenu()
{
    menuItems.resize(static_cast<size_t>(MenuOption::COUNT));

    menuItems[static_cast<size_t>(MenuOption::FULLSCREEN)].setString("Fullscreen: " + std::string(GameConfig::getInstance().isFullscreen() ? "ON" : "OFF"));
    menuItems[static_cast<size_t>(MenuOption::CONTROLS)].setString("Controls: " + std::string(GameConfig::getInstance().getControlScheme() == GameConfig::ControlScheme::WASD ? "WASD" : "Arrows"));
    menuItems[static_cast<size_t>(MenuOption::SOUND)].setString("Sound: " + std::to_string(static_cast<int>(GameConfig::getInstance().getMusicVolume())));
    menuItems[static_cast<size_t>(MenuOption::BACK)].setString("Back");

    for (auto& item : menuItems)
    {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updateMenuPositions();
}

void SettingsState::updateMenuPositions()
{
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 300.0f : 150.0f;
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f;
    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        sf::FloatRect textBounds = menuItems[i].getLocalBounds();
        float xPos = windowWidth / 2.0f - textBounds.width / 2.0f;
        menuItems[i].setPosition(xPos, startY + i * verticalSpacing);
    }

    for (auto& item : menuItems)
    {
        if (GameConfig::getInstance().isFullscreen())
        {
            item.setCharacterSize(80);
        }
        else
        {
            item.setCharacterSize(40);
        }
    }
}

void SettingsState::processEvents(sf::Event& event)
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
                case MenuOption::FULLSCREEN:
                    game->toggleFullscreen();
                    menuItems[static_cast<size_t>(MenuOption::FULLSCREEN)].setString("Fullscreen: " + std::string(GameConfig::getInstance().isFullscreen() ? "ON" : "OFF"));
                    updateMenuPositions();
                    break;
                case MenuOption::CONTROLS:
                {
                    if (GameConfig::getInstance().getControlScheme() == GameConfig::ControlScheme::WASD)
                    {
                        GameConfig::getInstance().setControlScheme(GameConfig::ControlScheme::ARROWS);
                    }
                    else
                    {
                        GameConfig::getInstance().setControlScheme(GameConfig::ControlScheme::WASD);
                    }
                    menuItems[static_cast<size_t>(MenuOption::CONTROLS)].setString("Controls: " + std::string(GameConfig::getInstance().getControlScheme() == GameConfig::ControlScheme::WASD ? "WASD" : "Arrows"));
                    break;
                }
                case MenuOption::SOUND:
                    break;
                case MenuOption::BACK:
                    game->setState(new MainMenuState(game, background));
                    break;
            }
        }

        if (selectedOption == MenuOption::SOUND)
        {
            float volume = GameConfig::getInstance().getMusicVolume();
            if (event.key.code == sf::Keyboard::Left)
            {
                volume -= 10.0f;
                if (volume >= 0.0f)  // Проверяем, чтобы не уйти в отрицательные значения
                {
                    GameConfig::getInstance().setMusicVolume(volume);
                    MusicManager::getInstance().setVolume(volume);
                    menuItems[static_cast<size_t>(MenuOption::SOUND)].setString("Sound: " + std::to_string(static_cast<int>(volume)));
                    selectSound.play();
                }
            }
            if (event.key.code == sf::Keyboard::Right)
            {
                volume += 10.0f;
                if (volume <= 100.0f)
                {
                    GameConfig::getInstance().setMusicVolume(volume);
                    MusicManager::getInstance().setVolume(volume);
                    menuItems[static_cast<size_t>(MenuOption::SOUND)].setString("Sound: " + std::to_string(static_cast<int>(volume)));
                    selectSound.play();
                }
            }
        }
    }
}

void SettingsState::update(float deltaTime)
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

void SettingsState::render(Renderer& renderer)
{
    renderer.clear(sf::Color::Black);
    if (background->getTexture())
    {
        renderer.render(*background);
    }
    else
    {
        Logger::getInstance().log("Background texture is missing in SettingsState!");
    }

    for (const auto& item : menuItems)
    {
        renderer.render(item);
    }
    renderer.display();
}