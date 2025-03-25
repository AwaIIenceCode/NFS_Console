//
// Created by AwallencePC on 25.03.2025.
//

#include "RecordsState.h"
#include "RecordsModeSelectionState.h"
#include "../../Config/Utils/Logger.h"
#include <fstream>
#include <sstream>
#include <algorithm>

RecordsState::RecordsState(Game* game, GameMode mode)
    : GameState(game), background(game->getRecordsBackground()), mode(mode) {
    if (!font.loadFromFile("Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for RecordsState");
    }

    titleText.setFont(font);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("Top 10 Records");

    backText.setFont(font);
    backText.setFillColor(sf::Color::Yellow);
    backText.setString("Back");

    loadRecords();
    updatePositions();
}

void RecordsState::loadRecords() {
    records.clear();
    recordTexts.clear();

    std::ifstream file("records.txt");
    if (file.is_open()) {
        std::string line;
        std::string modeStr = (mode == GameMode::TIME_TRIAL) ? "TimeTrial" : "Unknown";
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string recordMode;
            float recordTime;
            ss >> recordMode >> recordTime;
            if (recordMode == modeStr) {
                records.push_back(recordTime);
            }
        }
        file.close();
    } else {
        Logger::getInstance().log("Failed to open records.txt for reading");
    }

    std::sort(records.begin(), records.end());
    if (records.size() > 10) {
        records.resize(10);
    }

    for (size_t i = 0; i < records.size(); ++i) {
        sf::Text recordText;
        recordText.setFont(font);
        recordText.setFillColor(sf::Color::White);

        int minutes = static_cast<int>(records[i]) / 60;
        int seconds = static_cast<int>(records[i]) % 60;
        int milliseconds = static_cast<int>(records[i] * 1000) % 1000 / 10;
        std::stringstream ss;
        ss << (i + 1) << ". " << std::setfill('0') << std::setw(2) << minutes << ":"
           << std::setfill('0') << std::setw(2) << seconds << ":"
           << std::setfill('0') << std::setw(2) << milliseconds;
        recordText.setString(ss.str());
        recordTexts.push_back(recordText);
    }
}

void RecordsState::updatePositions() {
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f;
    float rightOffset = GameConfig::getInstance().isFullscreen() ? 800.0f : 300.0f;
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 75.0f : 40.0f;

    titleText.setPosition(windowWidth - rightOffset, startY);
    if (GameConfig::getInstance().isFullscreen()) {
        titleText.setCharacterSize(80);
    } else {
        titleText.setCharacterSize(40);
    }

    for (size_t i = 0; i < recordTexts.size(); ++i) {
        recordTexts[i].setPosition(windowWidth - rightOffset, startY + 100.0f + i * verticalSpacing);
        if (GameConfig::getInstance().isFullscreen()) {
            recordTexts[i].setCharacterSize(40);
        } else {
            recordTexts[i].setCharacterSize(20);
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
    renderer.render(*background);
    renderer.render(titleText);
    for (const auto& recordText : recordTexts) {
        renderer.render(recordText);
    }
    renderer.render(backText);
}