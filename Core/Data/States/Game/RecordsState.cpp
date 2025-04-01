//
// Created by AwallencePC on 25.03.2025.
//

#include "RecordsState.h"
#include "Core/Data/States/Menu/RecordsModeSelectionState.h"
#include "../../../Config/Utils/Logger.h"
#include <algorithm>

RecordsState::RecordsState(Game* game, GameMode mode)
    : GameState(game), background(game->getRecordsBackground()), mode(mode) {
    Logger::getInstance().log("RecordsState created");
    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for RecordsState");
    }

    titleText.setFont(font);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("Top 10 Records");

    noRecordsText.setFont(font);
    noRecordsText.setFillColor(sf::Color::White);
    noRecordsText.setString("No records yet");

    backText.setFont(font);
    backText.setFillColor(sf::Color::Yellow);
    backText.setString("Back");

    loadRecords();
    updatePositions();

}

RecordsState::~RecordsState()
{
    Logger::getInstance().log("RecordsState destructor called");
}

std::string RecordsState::formatTime(float time) {
    int minutes = static_cast<int>(time) / 60;
    int seconds = static_cast<int>(time) % 60;
    int milliseconds = static_cast<int>(time * 1000) % 1000 / 10;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds << ":"
       << std::setfill('0') << std::setw(2) << milliseconds;
    return ss.str();
}

void RecordsState::loadRecords() {
    records.clear();
    recordTexts.clear();

    records = SaveManager::getInstance().loadRecords(mode);

    std::sort(records.begin(), records.end());
    if (records.size() > 10) {
        records.resize(10);
    }

    for (size_t i = 0; i < records.size(); ++i) {
        sf::Text recordText;
        recordText.setFont(font);
        recordText.setFillColor(sf::Color::White);
        std::stringstream ss;
        ss << (i + 1) << ". " << formatTime(records[i]);
        recordText.setString(ss.str());
        recordTexts.push_back(recordText);
    }
}

void RecordsState::updatePositions() {
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f;
    float rightOffset = GameConfig::getInstance().isFullscreen() ? 400.0f : 350.0f; // Уменьшаем отступ
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 75.0f : 40.0f;

    titleText.setPosition(windowWidth - rightOffset, startY);
    if (GameConfig::getInstance().isFullscreen()) {
        titleText.setCharacterSize(80);
        noRecordsText.setCharacterSize(40);
    } else {
        titleText.setCharacterSize(40);
        noRecordsText.setCharacterSize(20);
    }

    if (records.empty()) {
        noRecordsText.setPosition(windowWidth - rightOffset, startY + 100.0f);
    } else {
        for (size_t i = 0; i < recordTexts.size(); ++i) {
            recordTexts[i].setPosition(windowWidth - rightOffset, startY + 100.0f + i * verticalSpacing);
            if (GameConfig::getInstance().isFullscreen()) {
                recordTexts[i].setCharacterSize(40);
            } else {
                recordTexts[i].setCharacterSize(20);
            }
        }
    }

    backText.setPosition(windowWidth - rightOffset, startY + 100.0f + recordTexts.size() * verticalSpacing + 50.0f);
    if (GameConfig::getInstance().isFullscreen()) {
        backText.setCharacterSize(40);
    } else {
        backText.setCharacterSize(20);
    }
}

void RecordsState::processEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
            game->setState(new RecordsModeSelectionState(game));
        }
    }
}

void RecordsState::update(float deltaTime) {
    updatePositions();
}

void RecordsState::render(Renderer& renderer) {
    Logger::getInstance().log("Rendering RecordsState");
    renderer.clear(sf::Color::Black); // Очищаем экран
    if (background->getTexture()) {
        renderer.render(*background);
    } else {
        Logger::getInstance().log("Records background texture is missing in RecordsState!");
    }
    renderer.render(titleText);
    if (records.empty()) {
        renderer.render(noRecordsText);
    } else {
        for (const auto& recordText : recordTexts) {
            renderer.render(recordText);
        }
    }
    renderer.render(backText);
    renderer.display();
}