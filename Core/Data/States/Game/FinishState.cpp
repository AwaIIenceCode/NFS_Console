//
// Created by AwallencePC on 25.03.2025.
//
// Core/Data/States/Game/FinishState.cpp
#include "FinishState.h"
#include "GameplayState.h"
#include "../../../Application/MainMenuState.h"
#include "../../../Config/Utils/Logger.h"
#include <sstream>
#include <iomanip>

FinishState::FinishState(Game* game, GameMode mode, float finishTime)
    : GameState(game, true), background(game->getRecordsBackground()), mode(mode), finishTime(finishTime),
      selectedOption(MenuOption::RESTART) {
    Logger::getInstance().log("FinishState created");
    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for FinishState");
    }

    if (!selectSoundBuffer.loadFromFile("J:/MyIDE/NFS_Console/Assets/Sounds/ChangeChoice.wav")) {
        Logger::getInstance().log("Failed to load menu select sound");
    }
    selectSound.setBuffer(selectSoundBuffer);

    finishMessage.setFont(font);
    finishMessage.setFillColor(sf::Color::White);
    finishMessage.setString("All done, finish, we're here!");

    timeText.setFont(font);
    timeText.setFillColor(sf::Color::White);
    int minutes = static_cast<int>(finishTime) / 60;
    int seconds = static_cast<int>(finishTime) % 60;
    int milliseconds = static_cast<int>(finishTime * 1000) % 1000 / 10;
    std::stringstream ss;
    ss << "Your Time: " << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds << ":"
       << std::setfill('0') << std::setw(2) << milliseconds;
    timeText.setString(ss.str());

    medalText.setFont(font);
    determineMedal();

    initializeMenu();
}

FinishState::~FinishState() {
    Logger::getInstance().log("FinishState destructor called");
}

void FinishState::initializeMenu() {
    menuItems.resize(static_cast<size_t>(MenuOption::COUNT));

    menuItems[static_cast<size_t>(MenuOption::RESTART)].setString("Restart");
    menuItems[static_cast<size_t>(MenuOption::MAIN_MENU)].setString("Main Menu");

    for (auto& item : menuItems) {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updateMenuPositions();
}

void FinishState::determineMedal() {
    const float goldThreshold = 50.0f;
    const float silverThreshold = 55.0f;
    const float bronzeThreshold = 60.0f;

    if (finishTime <= goldThreshold) {
        medalText.setFillColor(sf::Color::Yellow);
        medalText.setString("Gold Medal!");
    } else if (finishTime <= silverThreshold) {
        medalText.setFillColor(sf::Color(192, 192, 192));
        medalText.setString("Silver Medal!");
    } else if (finishTime <= bronzeThreshold) {
        medalText.setFillColor(sf::Color(205, 127, 50));
        medalText.setString("Bronze Medal!");
    } else {
        medalText.setFillColor(sf::Color::White);
        medalText.setString("No Medal");
    }
}

void FinishState::updateMenuPositions() {
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f;
    float rightOffset = GameConfig::getInstance().isFullscreen() ? 800.0f : 300.0f;
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 75.0f : 40.0f;

    finishMessage.setPosition(windowWidth - rightOffset, startY);
    timeText.setPosition(windowWidth - rightOffset, startY + verticalSpacing);
    medalText.setPosition(windowWidth - rightOffset, startY + 2 * verticalSpacing);

    for (size_t i = 0; i < menuItems.size(); ++i) {
        menuItems[i].setPosition(windowWidth - rightOffset, startY + (3 + i) * verticalSpacing);
    }

    if (GameConfig::getInstance().isFullscreen()) {
        finishMessage.setCharacterSize(80);
        timeText.setCharacterSize(40);
        medalText.setCharacterSize(40);
        for (auto& item : menuItems) {
            item.setCharacterSize(40);
        }
    } else {
        finishMessage.setCharacterSize(40);
        timeText.setCharacterSize(20);
        medalText.setCharacterSize(20);
        for (auto& item : menuItems) {
            item.setCharacterSize(20);
        }
    }
}

void FinishState::processEvents(sf::Event& event) {
    // Вызываем базовый метод, чтобы обработать переключение треков
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
                case MenuOption::RESTART:
                    game->setState(new GameplayState(game, game->getBackground(), mode));
                break;
                case MenuOption::MAIN_MENU:
                    game->setState(new MainMenuState(game, game->getBackground()));
                break;
            }
        }
    }
}

void FinishState::update(float deltaTime) {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (i == static_cast<size_t>(selectedOption)) {
            menuItems[i].setFillColor(sf::Color::Yellow);
        } else {
            menuItems[i].setFillColor(sf::Color::White);
        }
    }

    updateMenuPositions();
}

void FinishState::render(Renderer& renderer) {
    Logger::getInstance().log("Rendering FinishState");
    renderer.clear(sf::Color::Black); // Очищаем экран
    if (background->getTexture()) {
        renderer.render(*background);
    } else {
        Logger::getInstance().log("FinishState background texture is missing!");
    }
    renderer.render(finishMessage);
    renderer.render(timeText);
    renderer.render(medalText);
    for (const auto& item : menuItems) {
        renderer.render(item);
    }
    renderer.display();
}