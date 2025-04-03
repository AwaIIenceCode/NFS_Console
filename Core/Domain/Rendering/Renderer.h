//
// Created by AwallencePC on 18.03.2025.

#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

class Renderer
{
public:
    Renderer(sf::RenderWindow* window);

    void clear(sf::Color color = sf::Color::Black) const;
    void render(const sf::Drawable& drawable) const;
    void display() const;

private:
    sf::RenderWindow* window;
};

#endif //RENDERER_H