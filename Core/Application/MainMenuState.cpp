//
// Created by AwallencePC on 23.03.2025.
//

#include "MainMenuState.h"
#include "GameplayState.h"
#include "../Config/Utils/Logger.h"

MainMenuState::MainMenuState(Game* game, sf::Sprite* background)
    : GameState(game), background(background), selectedOption(MenuOption::START_GAME)
{
    if (!font.loadFromFile("Assets/Fonts/Pencils.ttf"))
    {
        Logger::getInstance().log("Failed to load font for MainMenuState");
    }

    // Загружаем звук для переключения пунктов меню
    if (!selectSoundBuffer.loadFromFile("Assets/Sounds/ChangeChoice.wav"))
    {
        Logger::getInstance().log("Failed to load menu select sound");
    }
    selectSound.setBuffer(selectSoundBuffer);

    initializeMenu();
}

void MainMenuState::initializeMenu()
{
    menuItems.resize(static_cast<size_t>(MenuOption::COUNT));

    // Настраиваем текст для каждой опции
    menuItems[static_cast<size_t>(MenuOption::START_GAME)].setString("Start Game");
    menuItems[static_cast<size_t>(MenuOption::SETTINGS)].setString("Settings");
    menuItems[static_cast<size_t>(MenuOption::EXIT_GAME)].setString("Exit Game");

    for (auto& item : menuItems)
    {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updateMenuPositions(); // Вызываем для начальной установки позиций
}

void MainMenuState::updateMenuPositions()
{
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 300.0f : 150.0f; // Разное начальное положение
    float rightOffset = GameConfig::getInstance().isFullscreen() ? 800.0f : 300.0f; // Разный отступ в зависимости от режима
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f; // Разный отступ между пунктами
    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].setPosition(windowWidth - rightOffset, startY + i * verticalSpacing);
    }

    // Обновляем размер текста при изменении режима
    for (auto& item : menuItems)
    {
        if (GameConfig::getInstance().isFullscreen()) { item.setCharacterSize(80); } // Больший размер в полноэкранном режиме
        else { item.setCharacterSize(40); } // Обычный размер в оконном режиме
    }
}

void MainMenuState::processEvents(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            // Переключаем выбор вверх
            int current = static_cast<int>(selectedOption);
            current = (current - 1 + static_cast<int>(MenuOption::COUNT)) % static_cast<int>(MenuOption::COUNT);
            selectedOption = static_cast<MenuOption>(current);
            selectSound.play();
        }

        if (event.key.code == sf::Keyboard::Down)
        {
            // Переключаем выбор вниз
            int current = static_cast<int>(selectedOption);
            current = (current + 1) % static_cast<int>(MenuOption::COUNT);
            selectedOption = static_cast<MenuOption>(current);
            selectSound.play();
        }

        if (event.key.code == sf::Keyboard::Enter)
        {
            // Подтверждение выбора
            switch (selectedOption)
            {
                case MenuOption::START_GAME:
                    // Переключаем состояние на GameplayState
                    game->setState(new GameplayState(game, background));
                    break;

                case MenuOption::SETTINGS:
                    // Заглушка для настроек
                    Logger::getInstance().log("Settings selected (not implemented yet)");
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
    // Обновляем подсветку выбранной опции
    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        if (i == static_cast<size_t>(selectedOption)) { menuItems[i].setFillColor(sf::Color::Yellow); }
        else { menuItems[i].setFillColor(sf::Color::White); }
    }

    // Обновляем позиции текста при изменении размера окна
    updateMenuPositions();
}

void MainMenuState::render(Renderer& renderer)
{
    renderer.render(*background);
    for (const auto& item : menuItems) { renderer.render(item); }
}