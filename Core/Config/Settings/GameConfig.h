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

    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }
    int getOriginalWindowWidth() const { return originalWindowWidth; }
    int getOriginalWindowHeight() const { return originalWindowHeight; }
    int getMaxFPS() const { return maxFPS; }
    bool isFullscreen() const { return fullscreen; }

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
          maxFPS(60), fullscreen(false) {}
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    int originalWindowWidth;  // Оригинальные размеры для оконного режима
    int originalWindowHeight;
    int windowWidth;          // Текущие размеры (могут меняться в полноэкранном режиме)
    int windowHeight;
    int maxFPS;
    bool fullscreen;
};

#endif