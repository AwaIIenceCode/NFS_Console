// Created by AwallencePC on 31.03.2025.

#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <random>
#include "../../../Config/Utils/Logger.h"

class MusicManager
{
public:
    static MusicManager& getInstance()
    {
        static MusicManager instance;
        return instance;
    }

    void initializeMenuPlaylist(const std::vector<std::string>& menuTracks)
    {
        menuPlaylist = menuTracks;
        if (!menuPlaylist.empty())
        {
            currentMenuTrackIndex = getRandomTrackIndex(menuPlaylist.size());
        }
    }

    void initializeGameplayPlaylist(const std::vector<std::string>& gameplayTracks)
    {
        gameplayPlaylist = gameplayTracks;
        if (!gameplayPlaylist.empty())
        {
            currentGameplayTrackIndex = getRandomTrackIndex(gameplayPlaylist.size());
        }
    }

    void playMenuMusic()
    {
        stopMusic();
        if (menuPlaylist.empty())
        {
            Logger::getInstance().log("Menu playlist is empty!");
            return;
        }

        if (currentMenuTrackIndex >= menuPlaylist.size())
        {
            currentMenuTrackIndex = 0;
        }

        if (music.openFromFile(menuPlaylist[currentMenuTrackIndex]))
        {
            music.setLoop(true);
            music.setVolume(volume);  // Используем текущую громкость
            music.play();
            Logger::getInstance().log("Playing menu music: " + menuPlaylist[currentMenuTrackIndex]);
        }
        else
        {
            Logger::getInstance().log("Failed to load menu music: " + menuPlaylist[currentMenuTrackIndex]);
        }
    }

    void playGameplayMusic()
    {
        stopMusic();
        if (gameplayPlaylist.empty())
        {
            Logger::getInstance().log("Gameplay playlist is empty!");
            return;
        }

        if (currentGameplayTrackIndex >= gameplayPlaylist.size())
        {
            currentGameplayTrackIndex = 0;
        }

        if (music.openFromFile(gameplayPlaylist[currentGameplayTrackIndex]))
        {
            music.setLoop(true);
            music.setVolume(volume);  // Используем текущую громкость
            music.play();
            Logger::getInstance().log("Playing gameplay music: " + gameplayPlaylist[currentGameplayTrackIndex]);
        }
        else
        {
            Logger::getInstance().log("Failed to load gameplay music: " + gameplayPlaylist[currentGameplayTrackIndex]);
        }
    }

    void nextTrack(bool isMenu)
    {
        stopMusic();
        if (isMenu)
        {
            if (menuPlaylist.empty()) return;
            currentMenuTrackIndex = (currentMenuTrackIndex + 1) % menuPlaylist.size();
            playMenuMusic();
        }
        else
        {
            if (gameplayPlaylist.empty()) return;
            currentGameplayTrackIndex = (currentGameplayTrackIndex + 1) % gameplayPlaylist.size();
            playGameplayMusic();
        }
    }

    void previousTrack(bool isMenu)
    {
        stopMusic();
        if (isMenu)
        {
            if (menuPlaylist.empty()) return;
            currentMenuTrackIndex = (currentMenuTrackIndex - 1 + menuPlaylist.size()) % menuPlaylist.size();
            playMenuMusic();
        }
        else
        {
            if (gameplayPlaylist.empty()) return;
            currentGameplayTrackIndex = (currentGameplayTrackIndex - 1 + gameplayPlaylist.size()) % gameplayPlaylist.size();
            playGameplayMusic();
        }
    }

    void stopMusic()
    {
        if (music.getStatus() == sf::Music::Playing)
        {
            music.stop();
            Logger::getInstance().log("Music stopped");
        }
    }

    void setVolume(float newVolume)
    {
        volume = newVolume;
        music.setVolume(volume);  // Обновляем громкость текущего трека
        Logger::getInstance().log("Music volume set to: " + std::to_string(volume));
    }

private:
    MusicManager() : currentMenuTrackIndex(0), currentGameplayTrackIndex(0), volume(50.0f)  // Начальная громкость 50
    {
        std::random_device rd;
        rng = std::mt19937(rd());
    }

    ~MusicManager()
    {
        stopMusic();
        Logger::getInstance().log("MusicManager destructor called");
    }

    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;

    size_t getRandomTrackIndex(size_t playlistSize)
    {
        if (playlistSize == 0) return 0;
        std::uniform_int_distribution<size_t> dist(0, playlistSize - 1);
        return dist(rng);
    }

    std::vector<std::string> menuPlaylist;
    std::vector<std::string> gameplayPlaylist;
    size_t currentMenuTrackIndex;
    size_t currentGameplayTrackIndex;
    sf::Music music;
    std::mt19937 rng;
    float volume;  // Переменная для хранения громкости
};

#endif // MUSICMANAGER_H