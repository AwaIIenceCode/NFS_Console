//
// Created by AwallencePC on 18.03.2025.
// Папка Input: Отвечает за обработку ввода игрока.
// InputHandler: Обрабатывает ввод с клавиатуры/геймпада для управления игроком.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>

class InputHandler {
public:
    static InputHandler& getInstance() {
        static InputHandler instance;
        return instance;
    }

    bool isKeyPressed(sf::Keyboard::Key key) const {
        return sf::Keyboard::isKeyPressed(key);
    }

    // Можно добавить методы для обработки событий, если нужно
    void processEvents(sf::Event& event) {
        // Пока пусто, но можно добавить обработку событий
    }

private:
    InputHandler() = default;
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
};

#endif //INPUTHANDLER_H