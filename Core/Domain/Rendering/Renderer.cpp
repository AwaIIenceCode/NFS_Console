//
// Created by AwallencePC on 18.03.2025.
//

#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& window) : window(window) {}

void Renderer::clear()
{
    window.clear(sf::Color::Black);
}

void Renderer::render(const sf::Drawable& drawable)
{
    window.draw(drawable);
}

void Renderer::display()
{
    window.display();
}