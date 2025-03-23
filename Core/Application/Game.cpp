//
// Created by AwallencePC on 19.03.2025.
//

#include "Game.h"

Game::Game()
    : window(), renderer(window)
{
    updateWindowSettings();

    // Загружаем текстуру фона через TextureManager
    sf::Texture* backgroundTexture = TextureManager::getInstance().loadTexture("J:/MyIDE/NFS_Console/Assets/Textures/background.jpg");
    if (backgroundTexture) {
        background.setTexture(*backgroundTexture);
        ScaleManager::getInstance().scaleSpriteToFill(background); // Заполняем окно
    } else {
        Logger::getInstance().log("Failed to load background texture, using default color");
    }

    Logger::getInstance().log("Game started");
}

Game::~Game()
{
    Logger::getInstance().log("Game closed");
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        // Переключение в полноэкранный режим по клавише F
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
            GameConfig::getInstance().setFullscreen(!GameConfig::getInstance().isFullscreen());
            updateWindowSettings();
            ScaleManager::getInstance().scaleSpriteToFill(background); // Перемасштабируем фон
        }
        // Выход из полноэкранного режима по клавише Esc
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (GameConfig::getInstance().isFullscreen()) {
                GameConfig::getInstance().setFullscreen(false);
                updateWindowSettings();
                ScaleManager::getInstance().scaleSpriteToFill(background); // Перемасштабируем фон
            }
        }
    }
}

void Game::update()
{
    // Пока пусто
}

void Game::render()
{
    renderer.clear();
    renderer.render(background);
    renderer.display();
}

void Game::updateWindowSettings()
{
    GameConfig& config = GameConfig::getInstance();
    if (config.isFullscreen()) {
        auto modes = sf::VideoMode::getFullscreenModes();
        if (!modes.empty()) {
            sf::VideoMode fullscreenMode = modes[0];
            config.setWindowSize(fullscreenMode.width, fullscreenMode.height);
            window.create(fullscreenMode, "NFS Console", sf::Style::Fullscreen);
        } else {
            window.create(sf::VideoMode(config.getWindowWidth(), config.getWindowHeight()), "NFS Console", sf::Style::Fullscreen);
        }
    } else {
        window.create(sf::VideoMode(config.getWindowWidth(), config.getWindowHeight()), "NFS Console", sf::Style::Default);
    }
    window.setFramerateLimit(config.getMaxFPS());
}