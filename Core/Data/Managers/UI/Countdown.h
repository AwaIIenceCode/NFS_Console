// Created by AwallencePC on 27.03.2025.
//

#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Config/Utils/Logger.h"
#include "../../../Domain/Rendering/Renderer.h"

class Countdown {
public:
    Countdown();
    void initialize();
    void update(float deltaTime);
    void render(Renderer& renderer);
    bool isCountingDown() const { return countingDown; }

private:
    bool countingDown;
    sf::Clock clock;
    sf::Text text;
    sf::Font font;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
};

#endif //COUNTDOWN_H