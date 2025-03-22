//
// Created by AwallencePC on 18.03.2025.
// Папка Rendering: Отвечает за отрисовку объектов на экране.
// Renderer: Отрисовывает игровые объекты (сортировка по z-order, вызов draw).
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

class Renderer
{
public:
    Renderer(sf::RenderWindow& window);
    void clear();
    void render(const sf::Drawable& drawable);
    void display();

private:
    sf::RenderWindow& window;
};



#endif //RENDERER_H
