// Created by AwallencePC on 18.03.2025.
//

#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow* window) : window(window) {}

void Renderer::clear(sf::Color color) const
{
    window->clear(color);
}

void Renderer::render(const sf::Drawable& drawable) const
{
    window->draw(drawable);
}

void Renderer::display() const
{
    window->display();
}