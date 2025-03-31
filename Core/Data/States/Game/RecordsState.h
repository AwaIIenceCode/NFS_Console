//
// Created by AwallencePC on 25.03.2025.
//

#ifndef RECORDSSTATE_H
#define RECORDSSTATE_H

#include "../GameState.h"
#include "../../../Application/Game.h"
#include "../../../Application/GameMode.h"
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Data/Managers/Utility/SaveManager.h" // Добавляем SaveManager
#include <SFML/Graphics.hpp>
#include <vector>
#include <iomanip>

class RecordsState : public GameState {
public:
    RecordsState(Game* game, GameMode mode);
    ~RecordsState(); // Добавляем деструктор
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    sf::Sprite* background;
    sf::Font font;
    sf::Text titleText;
    sf::Text noRecordsText;
    std::vector<sf::Text> recordTexts;
    sf::Text backText;
    GameMode mode;
    std::vector<float> records;

    void loadRecords();
    void updatePositions();
    std::string formatTime(float time);
};

#endif //RECORDSSTATE_H