//
// Created by AwallencePC on 23.03.2025.
//

#include "GameplayState.h"
#include "MainMenuState.h"

GameplayState::GameplayState(Game* game, sf::Sprite* background)
    : GameState(game), background(background), playerCar("Assets/Textures/player_car.png")
{
    // Устанавливаем начальную позицию машины
    playerCar.setPosition(GameConfig::getInstance().getWindowWidth() / 2.0f,
                          GameConfig::getInstance().getWindowHeight() / 2.0f);
    ScaleManager::getInstance().scaleSprite(playerCar.getSprite());
}

void GameplayState::processEvents(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            // Возвращаемся в главное меню
            game->setState(new MainMenuState(game, background));
        }
    }
}

void GameplayState::update(float deltaTime)
{
    playerCar.update(deltaTime);
}

void GameplayState::render(Renderer& renderer)
{
    renderer.render(*background);
    playerCar.render(renderer);
}