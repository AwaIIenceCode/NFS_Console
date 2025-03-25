//
// Created by AwallencePC on 23.03.2025.
//

#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "GameState.h"
#include "../../Application/Game.h"
#include "../../Application/GameMode.h"
#include "../../Domain/Entities/PlayerCar.h"
#include "../../Config/Settings/GameConfig.h"
#include "../../Config/Utils/ScaleManager.h"
#include <SFML/Audio.hpp>
#include <iomanip>
#include <vector>

class GameplayState : public GameState {
public:
    GameplayState(Game* game, sf::Sprite* background, GameMode mode);
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    sf::Sprite* background;
    PlayerCar playerCar;
    GameMode gameMode;

    // Переменные для отсчёта
    bool isCountingDown;
    sf::Clock countdownClock;
    sf::Text countdownText;
    sf::Font font;
    sf::SoundBuffer countdownBuffer;
    sf::Sound countdownSound;
    void initializeCountdown();
    void updateCountdown();

    // Переменные для трассы
    sf::Texture roadTexture;
    sf::Sprite road1;
    sf::Sprite road2;
    float roadWidth;
    float roadHeight;
    float roadSpeed;
    float totalDistance;
    float passedDistance;
    void initializeRoad();
    void updateRoad(float deltaTime);

    // Переменные для таймера
    sf::Clock gameTimer;
    sf::Text timerText;
    bool timerStarted;
    void updateTimer();

    // Переменные для прогресса
    sf::Text progressText; // Текст для отображения прогресса
    void updateProgress(); // Метод для обновления прогресса

    // Переменные для финиша
    float finishTime; // Время финиша в секундах
    bool raceFinished; // Флаг, что гонка завершена

    // Переменные для паузы
    bool isPaused; // Флаг паузы
    enum class PauseOption {
        RESUME,
        MAIN_MENU,
        COUNT
    };
    sf::Text pauseMessage;
    std::vector<sf::Text> pauseMenuItems;
    PauseOption selectedPauseOption;
    sf::SoundBuffer selectSoundBuffer;
    sf::Sound selectSound;
    void initializePauseMenu();
    void updatePauseMenuPositions();
};

#endif //GAMEPLAYSTATE_H