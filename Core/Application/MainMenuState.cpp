// Core/Application/MainMenuState.cpp
#include "MainMenuState.h"
#include "../Data/States/Menu/GameModeSelectionState.h"
#include "../Data/States/Menu/RecordsModeSelectionState.h"
#include "../Config/Utils/Logger.h"

MainMenuState::MainMenuState(Game* game, sf::Sprite* background)
    : GameState(game), background(background), selectedOption(MenuOption::START_GAME) {
    Logger::getInstance().log("MainMenuState created");
    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for MainMenuState");
    }

    // Загружаем звук для переключения пунктов меню
    if (!selectSoundBuffer.loadFromFile("J:/MyIDE/NFS_Console/Assets/Sounds/ChangeChoice.wav")) {
        Logger::getInstance().log("Failed to load menu select sound");
    }
    selectSound.setBuffer(selectSoundBuffer);

    initializeMenu();
}

MainMenuState::~MainMenuState() {
    Logger::getInstance().log("MainMenuState destructor called");
}

void MainMenuState::initializeMenu() {
    menuItems.resize(static_cast<size_t>(MenuOption::COUNT));

    // Настраиваем текст для каждой опции
    menuItems[static_cast<size_t>(MenuOption::START_GAME)].setString("Start Game");
    menuItems[static_cast<size_t>(MenuOption::RECORDS)].setString("Records");
    menuItems[static_cast<size_t>(MenuOption::SETTINGS)].setString("Settings");
    menuItems[static_cast<size_t>(MenuOption::EXIT_GAME)].setString("Exit Game");

    for (auto& item : menuItems) {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updateMenuPositions(); // Вызываем для начальной установки позиций
}

void MainMenuState::updateMenuPositions() {
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 300.0f : 150.0f; // Разное начальное положение
    float rightOffset = GameConfig::getInstance().isFullscreen() ? 800.0f : 300.0f; // Разный отступ в зависимости от режима
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f; // Разный отступ между пунктами
    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].setPosition(windowWidth - rightOffset, startY + i * verticalSpacing);
    }

    // Обновляем размер текста при изменении режима
    for (auto& item : menuItems) {
        if (GameConfig::getInstance().isFullscreen()) {
            item.setCharacterSize(80); // Больший размер в полноэкранном режиме
        } else {
            item.setCharacterSize(40); // Обычный размер в оконном режиме
        }
    }
}

void MainMenuState::processEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            // Переключаем выбор вверх
            int current = static_cast<int>(selectedOption);
            current = (current - 1 + static_cast<int>(MenuOption::COUNT)) % static_cast<int>(MenuOption::COUNT);
            selectedOption = static_cast<MenuOption>(current);
            selectSound.play();
        }

        if (event.key.code == sf::Keyboard::Down) {
            // Переключаем выбор вниз
            int current = static_cast<int>(selectedOption);
            current = (current + 1) % static_cast<int>(MenuOption::COUNT);
            selectedOption = static_cast<MenuOption>(current);
            selectSound.play();
        }

        if (event.key.code == sf::Keyboard::Enter) {
            // Подтверждение выбора
            switch (selectedOption) {
                case MenuOption::START_GAME:
                    // Переходим в меню выбора режима
                    game->setState(new GameModeSelectionState(game, background));
                    break;
                case MenuOption::RECORDS:
                    game->setState(new RecordsModeSelectionState(game));
                    break;
                case MenuOption::SETTINGS:
                    Logger::getInstance().log("Settings selected (not implemented yet)");
                    break;
                case MenuOption::EXIT_GAME:
                    game->close();
                    break;
            }
        }
    }
}

void MainMenuState::update(float deltaTime) {
    // Обновляем подсветку выбранной опции
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (i == static_cast<size_t>(selectedOption)) {
            menuItems[i].setFillColor(sf::Color::Yellow);
        } else {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }

    // Обновляем позиции текста при изменении размера окна
    updateMenuPositions();
}

void MainMenuState::render(Renderer& renderer) {
    renderer.clear(sf::Color::Black); // Очищаем экран чёрным цветом
    renderer.render(*background);
    for (const auto& item : menuItems) {
        renderer.render(item);
    }
    renderer.display(); // Обновляем экран
}