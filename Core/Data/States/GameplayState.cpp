//
// Created by AwallencePC on 23.03.2025.
//

#include "GameplayState.h"
#include "../../Application/MainMenuState.h"
#include "../../Config/Utils/Logger.h"

GameplayState::GameplayState(Game* game, sf::Sprite* background, GameMode mode)
    : GameState(game), background(background), playerCar("Assets/Textures/RedCar_1.png"),
      gameMode(mode), isCountingDown(true), roadSpeed(200.0f), totalDistance(8000.0f), passedDistance(0.0f) {
    // Устанавливаем начальную позицию машины (центр по X, нижняя треть по Y)
    playerCar.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f,
                          GameConfig::getInstance().getWindowHeight() * 2.0f / 3.0f);
    // Убираем ScaleManager для машины, так как масштаб уже задан в PlayerCar
    // ScaleManager::getInstance().scaleSprite(playerCar.getSprite());

    if (!font.loadFromFile("Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for GameplayState");
    }

    initializeCountdown();
    initializeRoad();
}

void GameplayState::initializeCountdown() {
    // Настраиваем текст отсчёта
    countdownText.setFont(font);
    countdownText.setCharacterSize(100);
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f - 50.0f,
                             GameConfig::getInstance().getWindowHeight() / 2.0f - 50.0f);
    countdownText.setString("3");

    // Загружаем звук отсчёта
    if (!countdownBuffer.loadFromFile("Assets/Sounds/StartSound_1.wav")) {
        Logger::getInstance().log("Failed to load countdown sound");
    }
    countdownSound.setBuffer(countdownBuffer);
    countdownSound.play(); // Проигрываем звук сразу
}

void GameplayState::updateCountdown() {
    float elapsed = countdownClock.getElapsedTime().asSeconds();
    if (elapsed < 1.0f) {
        countdownText.setString("3");
    } else if (elapsed < 2.0f) {
        countdownText.setString("2");
    } else if (elapsed < 3.0f) {
        countdownText.setString("1");
    } else if (elapsed < 4.0f) {
        countdownText.setString("Go!");
    } else {
        isCountingDown = false;
    }
}

void GameplayState::initializeRoad() {
    if (!roadTexture.loadFromFile("Assets/Textures/TimeTrialRoad.png")) {
        Logger::getInstance().log("Failed to load road texture");
        sf::Image image;
        image.create(400, 800, sf::Color(100, 100, 100, 255));
        if (!roadTexture.loadFromImage(image)) {
            Logger::getInstance().log("Failed to create road texture placeholder");
        }
    }

    road1.setTexture(roadTexture);
    road2.setTexture(roadTexture);

    // Устанавливаем ширину и высоту трассы до масштабирования
    roadWidth = static_cast<float>(roadTexture.getSize().x);
    roadHeight = static_cast<float>(roadTexture.getSize().y);

    // Центрируем дорогу по X
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float windowHeight = static_cast<float>(GameConfig::getInstance().getWindowHeight());
    float roadX = (windowWidth - roadWidth) / 2.0f;

    // Масштабируем спрайты
    ScaleManager::getInstance().scaleSprite(road1);
    ScaleManager::getInstance().scaleSprite(road2);

    // Учитываем масштаб при расчёте ширины и высоты
    float scaleY = road1.getScale().y;
    roadWidth *= road1.getScale().x;
    roadHeight *= scaleY;

    // Устанавливаем начальные позиции так, чтобы дорога покрывала весь экран
    // road1 должен начинаться так, чтобы его верхняя часть была на верхней границе экрана (y = 0)
    road1.setPosition(roadX, 0.0f);
    // road2 должен начинаться сразу над road1
    road2.setPosition(roadX, -roadHeight);

    // Логируем для отладки
    Logger::getInstance().log("Window height: " + std::to_string(windowHeight));
    Logger::getInstance().log("Road height after scaling: " + std::to_string(roadHeight));
    Logger::getInstance().log("road1 position: " + std::to_string(road1.getPosition().y));
    Logger::getInstance().log("road2 position: " + std::to_string(road2.getPosition().y));
}

void GameplayState::updateRoad(float deltaTime) {
    if (!isCountingDown) {
        float moveDistance = roadSpeed * deltaTime;
        road1.move(0.0f, moveDistance);
        road2.move(0.0f, moveDistance);
        passedDistance += moveDistance;

        // Если спрайт ушёл за нижнюю границу, перемещаем его наверх
        if (road1.getPosition().y >= GameConfig::getInstance().getWindowHeight()) {
            road1.setPosition(road1.getPosition().x, road2.getPosition().y - roadHeight);
        }
        if (road2.getPosition().y >= GameConfig::getInstance().getWindowHeight()) {
            road2.setPosition(road2.getPosition().x, road1.getPosition().y - roadHeight);
        }
    }
}

void GameplayState::processEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            game->setState(new MainMenuState(game, background));
        }
    }
}

void GameplayState::update(float deltaTime) {
    if (isCountingDown) {
        updateCountdown();
    } else {
        updateRoad(deltaTime);

        // Ограничиваем движение машины по ширине трассы
        float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
        float roadLeft = (windowWidth - roadWidth) / 2.0f;
        float roadRight = roadLeft + roadWidth;

        playerCar.update(deltaTime, roadLeft, roadRight);
    }
}

void GameplayState::render(Renderer& renderer) {
    renderer.render(road1);
    renderer.render(road2);
    playerCar.render(renderer);
    if (isCountingDown) {
        renderer.render(countdownText);
    }
}