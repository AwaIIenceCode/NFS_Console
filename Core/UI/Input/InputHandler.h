//
// Created by AwallencePC on 18.03.2025.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>

class InputHandler
{
public:
    static InputHandler& getInstance()
    {
        static InputHandler instance;
        return instance;
    }

    bool isKeyPressed(sf::Keyboard::Key key) const
    {
        return sf::Keyboard::isKeyPressed(key);
    }

    void processEvents(sf::Event& event) {}

private:
    InputHandler() = default;
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
};

#endif //INPUTHANDLER_H