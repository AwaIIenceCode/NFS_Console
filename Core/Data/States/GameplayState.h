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

class GameplayState : public GameState
{
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
    sf::Texture roadTexture; // Текстура дороги
    sf::Sprite road1; // Первый спрайт дороги
    sf::Sprite road2; // Второй спрайт дороги
    float roadWidth; // Ширина
    float roadHeight; // Переменная для высоты после масштабирования
    float roadSpeed; // Скорость прокрутки дороги
    float totalDistance; // Общая длина трассы
    float passedDistance; // Сколько проехали
    void initializeRoad();
    void updateRoad(float deltaTime);
};

#endif //GAMEPLAYSTATE_H
