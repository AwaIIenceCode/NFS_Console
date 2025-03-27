//
// Created by AwallencePC on 22.03.2025.
//

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "../Config/Utils/Logger.h"

class AudioManager
{
public:
    static AudioManager& getInstance()
    {
        static AudioManager instance;
        return instance;
    }

    // Загружаем звук по пути и даём ему имя
    void loadSound(const std::string& name, const std::string& path)
    {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(path))
        {
            Logger::getInstance().log("Failed to load sound: " + path);
            return;
        }
        soundBuffers[name] = buffer;
        sounds[name] = sf::Sound();
        sounds[name].setBuffer(soundBuffers[name]);
        Logger::getInstance().log("Loaded sound: " + path);
    }


    void playSound(const std::string& name)
    {
        auto it = sounds.find(name);
        if (it != sounds.end())
        {
            it->second.stop();
            it->second.play();
        }

        else
        {
            Logger::getInstance().log("Sound not found: " + name);
        }
    }

    void playLoopingSound(const std::string& name)
    {
        auto it = sounds.find(name);

        if (it != sounds.end())
        {
            it->second.setLoop(true);
            it->second.play();
        }

        else
        {
            Logger::getInstance().log("Looping sound not found: " + name);
        }
    }

    void stopLoopingSound(const std::string& name)
    {
        auto it = sounds.find(name);
        if (it != sounds.end())
        {
            it->second.setLoop(false);
            it->second.stop();
        }
    }

    void setPitch(const std::string& name, float pitch)
    {
        auto it = sounds.find(name);

        if (it != sounds.end())
        {
            it->second.setPitch(pitch);
        }
    }

    void setVolume(const std::string& name, float volume)
    {
        auto it = sounds.find(name);

        if (it != sounds.end())  { it->second.setVolume(volume); }
    }

private:
    AudioManager() = default;
    ~AudioManager() = default;
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
};

#endif //AUDIOMANAGER_H
