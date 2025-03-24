//
// Created by AwallencePC on 19.03.2025.
//

#include "Game.h"

Game::Game()
    : window(), renderer(window), currentState(nullptr)
{
    updateWindowSettings();

    // Загружаем текстуру фона через TextureManager
    sf::Texture* backgroundTexture = TextureManager::getInstance().loadTexture("Assets/Textures/BackgroundMenu.jpg");
    if (backgroundTexture)
    {
        background.setTexture(*backgroundTexture);
        ScaleManager::getInstance().scaleSpriteToFill(background);
    }

    else { Logger::getInstance().log("Failed to load background texture, using default color"); }

    // Устанавливаем начальное состояние — главное меню
    currentState = new MainMenuState(this, &background);

    Logger::getInstance().log("Game started");
}

Game::~Game()
{
    delete currentState;
    Logger::getInstance().log("Game closed");
}

void Game::run()
{
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
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

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
            GameConfig::getInstance().setFullscreen(!GameConfig::getInstance().isFullscreen());
            updateWindowSettings();
            ScaleManager::getInstance().scaleSpriteToFill(background);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            if (GameConfig::getInstance().isFullscreen())
            {
                GameConfig::getInstance().setFullscreen(false);
                updateWindowSettings();
                ScaleManager::getInstance().scaleSpriteToFill(background);
            }
        }

        currentState->processEvents(event);
    }
}

void Game::update(float deltaTime)
{
    currentState->update(deltaTime);
}

void Game::render()
{
    renderer.clear();
    currentState->render(renderer);
    renderer.display();
}

void Game::setState(GameState* newState)
{
    delete currentState;
    currentState = newState;
}

void Game::close()
{
    window.close();
}

void Game::updateWindowSettings()
{
    GameConfig& config = GameConfig::getInstance();
    if (config.isFullscreen())
     {
        auto modes = sf::VideoMode::getFullscreenModes();

        if (!modes.empty())
        {
            sf::VideoMode fullscreenMode = modes[0];
            config.setWindowSize(fullscreenMode.width, fullscreenMode.height);
            window.create(fullscreenMode, "NFS Console", sf::Style::Fullscreen);
        }

        else
        {
            window.create(sf::VideoMode(config.getWindowWidth(), config.getWindowHeight()), "NFS Console", sf::Style::Fullscreen);
        }
    }

    else
    {
        window.create(sf::VideoMode(config.getWindowWidth(), config.getWindowHeight()), "NFS Console", sf::Style::Default);
    }

    window.setFramerateLimit(config.getMaxFPS());
}