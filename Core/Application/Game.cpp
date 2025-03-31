// Core/Application/Game.cpp
#include "Game.h"
#include "MainMenuState.h"
#include "../../Core/Audio/AudioManager.h"

Game::Game()
    : window(sf::VideoMode(GameConfig::getInstance().getWindowWidth(), GameConfig::getInstance().getWindowHeight()), "NFS Console"), renderer(&window), currentState(nullptr) {
    window.setFramerateLimit(GameConfig::getInstance().getMaxFPS());

    // Загружаем текстуру для фона
    sf::Texture* backgroundTexture = TextureManager::getInstance().loadTexture("J:/MyIDE/NFS_Console/Assets/Textures/BackgroundMenu.jpg");
    if (backgroundTexture) {
        background.setTexture(*backgroundTexture);
        ScaleManager::getInstance().scaleSprite(background); // Раскомментируем
    } else {
        Logger::getInstance().log("Failed to load background texture");
    }

    // Загружаем текстуру для фона экрана рекордов
    sf::Texture* recordsBackgroundTexture = TextureManager::getInstance().loadTexture("J:/MyIDE/NFS_Console/Assets/Textures/BackgroundRecords.jpg");
    if (recordsBackgroundTexture) {
        recordsBackground.setTexture(*recordsBackgroundTexture);
        ScaleManager::getInstance().scaleSprite(recordsBackground); // Раскомментируем
    } else {
        Logger::getInstance().log("Failed to load records background texture");
    }

    setState(new MainMenuState(this, &background));
}

Game::~Game() {
    Logger::getInstance().log("Game destructor called");
    AudioManager::getInstance().stopAllSounds(); // Останавливаем все звуки
    delete currentState;
    Logger::getInstance().log("Game destructor finished");
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (currentState) {
                currentState->processEvents(event);
            }
        }

        float deltaTime = clock.restart().asSeconds();
        if (currentState) {
            currentState->update(deltaTime);
            currentState->render(renderer);
        }
    }
}

void Game::setState(GameState* state) {
    delete currentState;
    currentState = state;
}

void Game::close() {
    window.close();
}

sf::Sprite* Game::getBackground() {
    return &background;
}

sf::Sprite* Game::getRecordsBackground() {
    return &recordsBackground;
}