// Core/Domain/Rendering/TextureManager.cpp
#include "TextureManager.h"
#include "../../../Core/Config/Utils/Logger.h"

sf::Texture* TextureManager::loadTexture(const std::string& path) {
    // Проверяем, есть ли текстура в хранилище
    auto it = textures.find(path);
    if (it != textures.end()) {
        return &it->second;
    }

    // Загружаем новую текстуру
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        Logger::getInstance().log("Failed to load texture: " + path);
        return nullptr;
    }

    // Сохраняем текстуру в хранилище
    textures[path] = texture;
    Logger::getInstance().log("Loaded texture: " + path);
    return &textures[path];
}

sf::Texture* TextureManager::addTexture(const std::string& key, const sf::Texture& texture) {
    textures[key] = texture;
    return &textures[key];
}

TextureManager::~TextureManager() {
    Logger::getInstance().log("TextureManager destructor called");
    textures.clear();
    Logger::getInstance().log("TextureManager destructor finished");
}