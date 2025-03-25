//
// Created by AwallencePC on 23.03.2025.
//

#include "GameplayState.h"
#include "../../Application/MainMenuState.h"
#include "FinishState.h"
#include "../../Config/Utils/Logger.h"
#include <fstream>

GameplayState::GameplayState(Game* game, sf::Sprite* background, GameMode mode)
    : GameState(game), background(background), playerCar("Assets/Textures/PurpleCar_1.png"),
      gameMode(mode), isCountingDown(true), roadSpeed(200.0f), totalDistance(8000.0f), passedDistance(0.0f),
      timerStarted(false), finishTime(0.0f), raceFinished(false), isPaused(false),
      selectedPauseOption(PauseOption::RESUME) {
    playerCar.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f,
                          GameConfig::getInstance().getWindowHeight() * 2.0f / 3.0f);

    if (!font.loadFromFile("Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for GameplayState");
    }

    if (!selectSoundBuffer.loadFromFile("Assets/Sounds/ChangeChoice.wav")) {
        Logger::getInstance().log("Failed to load menu select sound");
    }
    selectSound.setBuffer(selectSoundBuffer);

    timerText.setFont(font);
    timerText.setCharacterSize(40);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(20.0f, 20.0f);

    progressText.setFont(font);
    progressText.setCharacterSize(40);
    progressText.setFillColor(sf::Color::White);
    progressText.setPosition(20.0f, 70.0f);

    initializeCountdown();
    initializeRoad();
    initializePauseMenu();
}

void GameplayState::initializeCountdown() {
    countdownText.setFont(font);
    countdownText.setCharacterSize(100);
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f - 50.0f,
                             GameConfig::getInstance().getWindowHeight() / 2.0f - 50.0f);
    countdownText.setString("3");

    if (!countdownBuffer.loadFromFile("Assets/Sounds/StartSound_1.wav")) {
        Logger::getInstance().log("Failed to load countdown sound");
    }
    countdownSound.setBuffer(countdownBuffer);
    countdownSound.play();
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

    roadWidth = static_cast<float>(roadTexture.getSize().x);
    roadHeight = static_cast<float>(roadTexture.getSize().y);

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
    road1.setPosition(roadX, -roadHeight + windowHeight); // Нижняя часть road1 на нижней границе экрана
    road2.setPosition(roadX, -roadHeight * 2.0f + windowHeight); // road2 сразу над road1

    // Логируем для отладки
    Logger::getInstance().log("Window height: " + std::to_string(windowHeight));
    Logger::getInstance().log("Road height after scaling: " + std::to_string(roadHeight));
    Logger::getInstance().log("road1 position: " + std::to_string(road1.getPosition().y));
    Logger::getInstance().log("road2 position: " + std::to_string(road2.getPosition().y));
}

void GameplayState::initializePauseMenu() {
    pauseMessage.setFont(font);
    pauseMessage.setFillColor(sf::Color::White);
    pauseMessage.setString("Paused");

    pauseMenuItems.resize(static_cast<size_t>(PauseOption::COUNT));
    pauseMenuItems[static_cast<size_t>(PauseOption::RESUME)].setString("Resume");
    pauseMenuItems[static_cast<size_t>(PauseOption::MAIN_MENU)].setString("Main Menu");

    for (auto& item : pauseMenuItems) {
        item.setFont(font);
        item.setFillColor(sf::Color::White);
    }

    updatePauseMenuPositions();
}

void GameplayState::updatePauseMenuPositions() {
    float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
    float startY = GameConfig::getInstance().isFullscreen() ? 150.0f : 75.0f;
    float rightOffset = GameConfig::getInstance().isFullscreen() ? 800.0f : 300.0f;
    float verticalSpacing = GameConfig::getInstance().isFullscreen() ? 75.0f : 40.0f;

    pauseMessage.setPosition(windowWidth - rightOffset, startY);

    for (size_t i = 0; i < pauseMenuItems.size(); ++i) {
        pauseMenuItems[i].setPosition(windowWidth - rightOffset, startY + (1 + i) * verticalSpacing);
    }

    if (GameConfig::getInstance().isFullscreen()) {
        pauseMessage.setCharacterSize(80);
        for (auto& item : pauseMenuItems) {
            item.setCharacterSize(40);
        }
    } else {
        pauseMessage.setCharacterSize(40);
        for (auto& item : pauseMenuItems) {
            item.setCharacterSize(20);
        }
    }
}

void GameplayState::updateRoad(float deltaTime) {
    if (!isCountingDown && !isPaused) {
        float moveDistance = roadSpeed * deltaTime;
        road1.move(0.0f, moveDistance);
        road2.move(0.0f, moveDistance);
        passedDistance += moveDistance;

        float windowHeight = static_cast<float>(GameConfig::getInstance().getWindowHeight());
        if (road1.getPosition().y >= windowHeight) {
            road1.setPosition(road1.getPosition().x, road2.getPosition().y - roadHeight);
        }
        if (road2.getPosition().y >= windowHeight) {
            road2.setPosition(road2.getPosition().x, road1.getPosition().y - roadHeight);
        }
    }
}

void GameplayState::updateTimer() {
    if (timerStarted && !isPaused) {
        sf::Time elapsed = gameTimer.getElapsedTime();
        int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
        int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
        int milliseconds = static_cast<int>(elapsed.asMilliseconds()) % 1000 / 10;

        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << minutes << ":"
           << std::setfill('0') << std::setw(2) << seconds << ":"
           << std::setfill('0') << std::setw(2) << milliseconds;
        timerText.setString(ss.str());
    }
}

void GameplayState::updateProgress() {
    float progress = (passedDistance / totalDistance) * 100.0f;
    if (progress > 100.0f) progress = 100.0f;
    std::stringstream ss;
    ss << "Progress: " << static_cast<int>(progress) << "%";
    progressText.setString(ss.str());
}

void GameplayState::processEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape && !isCountingDown && !raceFinished) {
            isPaused = !isPaused; // Переключаем состояние паузы
        }

        if (isPaused) {
            if (event.key.code == sf::Keyboard::Up) {
                int current = static_cast<int>(selectedPauseOption);
                current = (current - 1 + static_cast<int>(PauseOption::COUNT)) % static_cast<int>(PauseOption::COUNT);
                selectedPauseOption = static_cast<PauseOption>(current);
                selectSound.play();
            }

            if (event.key.code == sf::Keyboard::Down) {
                int current = static_cast<int>(selectedPauseOption);
                current = (current + 1) % static_cast<int>(PauseOption::COUNT);
                selectedPauseOption = static_cast<PauseOption>(current);
                selectSound.play();
            }

            if (event.key.code == sf::Keyboard::Enter) {
                switch (selectedPauseOption) {
                    case PauseOption::RESUME:
                        isPaused = false;
                        break;
                    case PauseOption::MAIN_MENU:
                        game->setState(new MainMenuState(game, background));
                        break;
                }
            }
        }
    }
}

void GameplayState::update(float deltaTime) {
    if (isCountingDown) {
        updateCountdown();
        if (!isCountingDown) {
            timerStarted = true;
            gameTimer.restart();
        }
    } else if (!raceFinished && !isPaused) {
        updateRoad(deltaTime);
        float windowWidth = static_cast<float>(GameConfig::getInstance().getWindowWidth());
        float roadLeft = (windowWidth - roadWidth) / 2.0f;
        float roadRight = roadLeft + roadWidth;
        playerCar.update(deltaTime, roadLeft, roadRight);
        updateTimer();
        updateProgress();

        if (passedDistance >= totalDistance) {
            raceFinished = true;
            finishTime = gameTimer.getElapsedTime().asSeconds();
            Logger::getInstance().log("Race finished! Time: " + std::to_string(finishTime) + " seconds");

            // Сохраняем результат в файл
            std::ofstream file("records.txt", std::ios::app); // Открываем файл в режиме добавления
            if (file.is_open()) {
                std::string modeStr = (gameMode == GameMode::TIME_TRIAL) ? "TimeTrial" : "Unknown";
                file << modeStr << " " << finishTime << "\n";
                file.close();
                Logger::getInstance().log("Result saved: " + modeStr + " " + std::to_string(finishTime));
            } else {
                Logger::getInstance().log("Failed to open records.txt for saving");
            }

            // Переходим на экран финиша
            game->setState(new FinishState(game, gameMode, finishTime));
        }
    }

    if (isPaused) {
        for (size_t i = 0; i < pauseMenuItems.size(); ++i) {
            if (i == static_cast<size_t>(selectedPauseOption)) {
                pauseMenuItems[i].setFillColor(sf::Color::Yellow);
            } else {
                pauseMenuItems[i].setFillColor(sf::Color::White);
            }
        }
        updatePauseMenuPositions();
    }
}

void GameplayState::render(Renderer& renderer) {
    renderer.render(road1);
    renderer.render(road2);
    playerCar.render(renderer);
    if (isCountingDown) {
        renderer.render(countdownText);
    }
    renderer.render(timerText);
    renderer.render(progressText);

    if (isPaused) {
        renderer.render(pauseMessage);
        for (const auto& item : pauseMenuItems) {
            renderer.render(item);
        }
    }
}