// Created by AwallencePC on 18.03.2025.
// TextureManager: Загружает и хранит текстуры для оптимизации.
//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {
public:
    // Получить единственный экземпляр (синглтон)
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    // Загрузить текстуру по пути, вернуть указатель
    sf::Texture* loadTexture(const std::string& path);

    // Добавить программно созданную текстуру
    sf::Texture* addTexture(const std::string& key, const sf::Texture& texture);

private:
    TextureManager() = default;
    ~TextureManager();

    // Запрещаем копирование
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    std::map<std::string, sf::Texture> textures; // Хранилище текстур
};

#endif //TEXTUREMANAGER_H