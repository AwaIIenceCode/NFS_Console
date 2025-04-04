// Created by AwallencePC on 19.03.2025.

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <algorithm>

class GameConfig
{
public:
    static GameConfig& getInstance()
    {
        static GameConfig instance;
        return instance;
    }

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
    ControlScheme getControlScheme() const { return controlScheme; }
    void setControlScheme(ControlScheme scheme) { controlScheme = scheme; }

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
            windowWidth = originalWindowWidth;
            windowHeight = originalWindowHeight;
        }
    }

    float getMusicVolume() const { return musicVolume; }

    void setMusicVolume(float volume)
    {
        musicVolume = std::max(0.0f, std::min(100.0f, volume));
    }

private:
    GameConfig()
        : originalWindowWidth(800), originalWindowHeight(600),
          windowWidth(800), windowHeight(600),
          maxFPS(60), fullscreen(false), controlScheme(ControlScheme::WASD),
          musicVolume(50.0f) {}
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    int originalWindowWidth;
    int originalWindowHeight;
    int windowWidth;
    int windowHeight;
    int maxFPS;
    bool fullscreen;
    ControlScheme controlScheme;
    float musicVolume;
};

#endif