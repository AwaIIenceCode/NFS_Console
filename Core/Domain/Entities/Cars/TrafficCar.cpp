// Created by AwallencePC on 30.03.2025.
//

#include "TrafficCar.h"
#include <cstdlib>
#include "../../../Config/Settings/GameConfig.h"
#include "../../../Config/Utils/Logger.h"


TrafficCar::TrafficCar(const std::string& texturePath, float roadLeft, float roadRight)
    : Car(texturePath) {
    // Устанавливаем рандомную скорость в диапазоне 100-300 пикселей/сек
    trafficSpeed = 100.0f + static_cast<float>(rand() % 201); // от 100 до 300
    Logger::getInstance().log("TrafficCar spawned with speed: " + std::to_string(trafficSpeed));

    // Масштабируем машинку (как PlayerCar, чтобы не была огромной)
    sprite.setScale(0.2f, 0.2f);

    // Позиция: рандомно в пределах дороги с отступами от тротуаров
    float sidewalkWidth = 100.0f;
    float carWidth = sprite.getGlobalBounds().width;
    float spawnRange = (roadRight - sidewalkWidth) - (roadLeft + sidewalkWidth) - carWidth;
    if (spawnRange < 0) spawnRange = 0;
    float xPos = (roadLeft + sidewalkWidth) + static_cast<float>(rand() % static_cast<int>(spawnRange));
    sprite.setPosition(xPos, -sprite.getGlobalBounds().height); // Спавним выше экрана

    Logger::getInstance().log("TrafficCar spawned at x: " + std::to_string(xPos));
}

void TrafficCar::update(float deltaTime, float roadSpeed) {
    // Двигаем машинку вниз с её собственной скоростью
    sprite.move(0.0f, trafficSpeed * deltaTime);
}

void TrafficCar::render(Renderer& renderer) const {
    renderer.render(sprite);
}

sf::FloatRect TrafficCar::getBounds() const {
    return sprite.getGlobalBounds();
}

bool TrafficCar::isOffScreen() const {
    return sprite.getPosition().y > GameConfig::getInstance().getWindowHeight() + sprite.getGlobalBounds().height;
}

sf::Vector2f TrafficCar::getPosition() const {
    return sprite.getPosition();
}