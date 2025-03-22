//
// Created by AwallencePC on 19.03.2025.
// Папка Config: Хранит конфигурации игры (размер окна, параметры машин).
// GameConfig: Хранит настройки игры (размер окна, FPS, параметры машин).
//

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

class GameConfig
{
public:
    // Получить единственный экземпляр (синглтон)
    static GameConfig& getInstance()
    {
        static GameConfig instance;
        return instance;
    }

    // Геттеры для настроек
    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }
    int getMaxFPS() const { return maxFPS; }

private:
    // Приватный конструктор для синглтона
    GameConfig() : windowWidth(800), windowHeight(600), maxFPS(60) {}

    // Запрещаем копирование
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    // Настройки
    int windowWidth;
    int windowHeight;
    int maxFPS;
};



#endif //GAMECONFIG_H
