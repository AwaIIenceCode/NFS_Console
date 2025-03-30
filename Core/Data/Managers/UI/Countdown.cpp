// Created by AwallencePC on 26.03.2025.
//

#include "Countdown.h"

Countdown::Countdown() : countingDown(true) {}

void Countdown::initialize() {
    if (!font.loadFromFile("J:/MyIDE/NFS_Console/Assets/Fonts/Pencils.ttf")) {
        Logger::getInstance().log("Failed to load font for Countdown");
    }

    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f - 50.0f,
                     GameConfig::getInstance().getWindowHeight() / 2.0f - 50.0f);
    text.setString("3");

    if (!soundBuffer.loadFromFile("J:/MyIDE/NFS_Console/Assets/Sounds/StartSound_1.wav")) {
        Logger::getInstance().log("Failed to load countdown sound");
    }

    sound.setBuffer(soundBuffer);
    sound.play();
}

void Countdown::update(float deltaTime) {
    float elapsed = clock.getElapsedTime().asSeconds();
    if (elapsed < 1.0f) { text.setString("3"); }
    else if (elapsed < 2.0f) { text.setString("2"); }
    else if (elapsed < 3.0f) { text.setString("1"); }
    else if (elapsed < 4.0f) { text.setString("Go!"); }
    else { countingDown = false; }
}

void Countdown::render(Renderer& renderer) {
    if (countingDown) {
        renderer.render(text);
    }
}