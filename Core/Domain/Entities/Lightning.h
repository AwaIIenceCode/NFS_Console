// Created by AwallencePC on 25.03.2025.
//

#ifndef NFS_CONSOLE_LIGHTNING_H
#define NFS_CONSOLE_LIGHTNING_H

#include "SpawnableEntity.h"
#include "../../Config/Settings/GameConfig.h"
#include "../../Config/Utils/Logger.h"

class Lightning : public SpawnableEntity {
public:
    Lightning(const std::string& texturePath, float roadLeft, float roadRight);
    void update(float deltaTime, float roadSpeed) override;
    void render(Renderer& renderer) const override;
    sf::FloatRect getBounds() const override;
    bool isOffScreen() const override;
    sf::Vector2f getPosition() const override;

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //NFS_CONSOLE_LIGHTNING_H