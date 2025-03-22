//
// Created by AwallencePC on 18.03.2025.
//

#include "Game.h"

Game::Game()
{
    window.create(sf::VideoMode(800, 600), "Racing Game");
    window.setFramerateLimit(60);
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
    // Пока пусто
}

void Game::render()
{
    window.clear(sf::Color::Black);
    window.display();
}