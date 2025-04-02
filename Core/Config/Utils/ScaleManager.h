//
// Created by AwallencePC on 23.03.2025.
//

#ifndef SCALEMANAGER_H
#define SCALEMANAGER_H

#include <SFML/Graphics.hpp>
#include "../Settings/GameConfig.h"

class ScaleManager
{
public:
    static ScaleManager& getInstance()
    {
        static ScaleManager instance;
        return instance;
    }

    void scaleSprite(sf::Sprite& sprite) const
    {
        const sf::Texture* texture = sprite.getTexture();
        if (!texture) return;

        float scaleX = static_cast<float>(GameConfig::getInstance().getWindowWidth()) / texture->getSize().x;
        float scaleY = static_cast<float>(GameConfig::getInstance().getWindowHeight()) / texture->getSize().y;
        float scale = std::min(scaleX, scaleY);
        sprite.setScale(scale, scale);

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setPosition(
            (GameConfig::getInstance().getWindowWidth() - bounds.width * scale) / 2.0f,
            (GameConfig::getInstance().getWindowHeight() - bounds.height * scale) / 2.0f
        );
    }

    void scaleSpriteToFill(sf::Sprite& sprite) const
    {
        const sf::Texture* texture = sprite.getTexture();
        if (!texture) return;

        float scaleX = static_cast<float>(GameConfig::getInstance().getWindowWidth()) / texture->getSize().x;
        float scaleY = static_cast<float>(GameConfig::getInstance().getWindowHeight()) / texture->getSize().y;
        float scale = std::max(scaleX, scaleY); // Используем больший коэффициент

        sprite.setScale(scale, scale);

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setPosition(
            (GameConfig::getInstance().getWindowWidth() - bounds.width * scale) / 2.0f,
            (GameConfig::getInstance().getWindowHeight() - bounds.height * scale) / 2.0f
        );
    }

private:
    ScaleManager() = default;
    ScaleManager(const ScaleManager&) = delete;
    ScaleManager& operator=(const ScaleManager&) = delete;
};

#endif