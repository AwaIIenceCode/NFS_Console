//
// Created by AwallencePC on 19.03.2025.
//

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

class GameConfig
{
public:
    static GameConfig& getInstance()
    {
        static GameConfig instance;
        return instance;
    }

    // Добавляем перечисление для схемы управления
    enum class ControlScheme
    {
        WASD,
        ARROWS
    };

    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }
    int getOriginalWindowWidth() const { return originalWindowWidth; }
    int getOriginalWindowHeight() const { return originalWindowHeight; }
    int getMaxFPS() const { return maxFPS; }
    bool isFullscreen() const { return fullscreen; }
    ControlScheme getControlScheme() const { return controlScheme; } // Геттер для схемы управления
    void setControlScheme(ControlScheme scheme) { controlScheme = scheme; } // Сеттер для схемы управления

    void setWindowSize(int width, int height)
    {
        windowWidth = width;
        windowHeight = height;
    }

    void setFullscreen(bool enable)
    {
        fullscreen = enable;
        if (!enable)
        {
            // Восстанавливаем оригинальные размеры при выходе из полноэкранного режима
            windowWidth = originalWindowWidth;
            windowHeight = originalWindowHeight;
        }
    }

private:
    GameConfig()
        : originalWindowWidth(800), originalWindowHeight(600),
          windowWidth(800), windowHeight(600),
          maxFPS(60), fullscreen(false), controlScheme(ControlScheme::WASD) {} // По умолчанию WASD
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    int originalWindowWidth;  // Оригинальные размеры для оконного режима
    int originalWindowHeight;
    int windowWidth;          // Текущие размеры (могут меняться в полноэкранном режиме)
    int windowHeight;
    int maxFPS;
    bool fullscreen;
    ControlScheme controlScheme; // Текущая схема управления
};

#endif