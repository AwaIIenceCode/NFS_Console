//
// Created by AwallencePC on 25.03.2025.
//


#ifndef NFS_CONSOLE_LIGHTNING_H
#define NFS_CONSOLE_LIGHTNING_H

#include <SFML/Graphics.hpp>
#include "../../../Core/Domain/Rendering/Renderer.h"
#include "../../Config/Settings/GameConfig.h"
#include "../../Config/Utils/ScaleManager.h"

class Lightning
{
public:
    Lightning(const std::string& texturePath, float roadLeft, float roadRight);
    void update(float deltaTime, float roadSpeed);
    void render(Renderer& renderer) const;
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
    sf::Vector2f getPosition() const;
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //NFS_CONSOLE_LIGHTNING_H