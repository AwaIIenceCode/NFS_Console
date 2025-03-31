// Core/Data/States/RecordsModeSelectionState.cpp
#include "RecordsModeSelectionState.h"
#include "../../../Application/MainMenuState.h"
#include "../Game/RecordsState.h"
#include "../../../Config/Utils/Logger.h"

RecordsModeSelectionState::RecordsModeSelectionState(Game* game)
    : GameState(game, true), background(game->getRecordsBackground()), selectedOption(MenuOption::TIME_TRIAL) {
    Logger::getInstance().log("RecordsModeSelectionState created");
    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for RecordsModeSelectionState");
    }

    if (!selectSoundBuffer.loadFromFile("J:/MyIDE/NFS_Console/Assets/Sounds/ChangeChoice.wav")) {
        Logger::getInstance().log("Failed to load menu select sound");
    }
    selectSound.setBuffer(selectSoundBuffer);

    initializeMenu();
}

RecordsModeSelectionState::~RecordsModeSelectionState() {
    Logger::getInstance().log("RecordsModeSelectionState destructor called");
}

void RecordsModeSelectionState::initializeMenu() {
    menuItems.resize(static_cast<size_t>(MenuOption::COUNT));

    menuItems[static_cast<size_t>(MenuOption::TIME_TRIAL)].setString("Time Trial");
    menuItems[static_cast<size_t>(MenuOption::BACK)].setString("Back");

    for (auto& item : menuItems) {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updateMenuPositions();
}

void RecordsModeSelectionState::updateMenuPositions() {
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 300.0f : 150.0f;
    float rightOffset = GameConfig::getInstance().isFullscreen() ? 800.0f : 300.0f;
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f;
    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].setPosition(windowWidth - rightOffset, startY + i * verticalSpacing);
    }

    for (auto& item : menuItems) {
        if (GameConfig::getInstance().isFullscreen()) {
            item.setCharacterSize(80);
        } else {
            item.setCharacterSize(40);
        }
    }
}

void RecordsModeSelectionState::processEvents(sf::Event& event) {

    GameState::processEvents(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            int current = static_cast<int>(selectedOption);
            current = (current - 1 + static_cast<int>(MenuOption::COUNT)) % static_cast<int>(MenuOption::COUNT);
            selectedOption = static_cast<MenuOption>(current);
            selectSound.play();
        }

        if (event.key.code == sf::Keyboard::Down) {
            int current = static_cast<int>(selectedOption);
            current = (current + 1) % static_cast<int>(MenuOption::COUNT);
            selectedOption = static_cast<MenuOption>(current);
            selectSound.play();
        }

        if (event.key.code == sf::Keyboard::Enter) {
            switch (selectedOption) {
                case MenuOption::TIME_TRIAL:
                    game->setState(new RecordsState(game, GameMode::TIME_TRIAL));
                break;
                case MenuOption::BACK:
                    game->setState(new MainMenuState(game, game->getBackground()));
                break;
            }
        }
    }
}

void RecordsModeSelectionState::update(float deltaTime) {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (i == static_cast<size_t>(selectedOption)) {
            menuItems[i].setFillColor(sf::Color::Yellow);
        } else {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }

    updateMenuPositions();
}

void RecordsModeSelectionState::render(Renderer& renderer) {
    Logger::getInstance().log("Rendering RecordsModeSelectionState");
    renderer.clear(sf::Color::Black); // Очищаем экран
    if (background->getTexture()) {
        renderer.render(*background);
    } else {
        Logger::getInstance().log("Records background texture is missing!");
    }
    for (const auto& item : menuItems) {
        renderer.render(item);
    }
    renderer.display(); // Обновляем экран
}