#include "Game.h"

Game::Game()
    : window(sf::VideoMode(GameConfig::getInstance().getWindowWidth(),
                           GameConfig::getInstance().getWindowHeight()), "NFS Console"),
      renderer(window)  // Передаём ссылку на window в конструктор renderer
{
    window.setFramerateLimit(GameConfig::getInstance().getMaxFPS());
    // Логируем старт игры
    Logger::getInstance().log("Game started");
}

Game::~Game()
{
    // Логируем закрытие игры
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
    }
}

void Game::update()
{
    // Пока пусто, добавлю логику обновления игры тут
}

void Game::render()
{
    window.clear(sf::Color::Black);
    window.display();
}