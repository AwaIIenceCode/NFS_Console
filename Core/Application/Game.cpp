#include "Game.h"
#include "MainMenuState.h"
#include "../../Core/Data/Managers/Audio/AudioManager.h"
#include "../../Core/Data/Managers/Audio/MusicManager.h"
#include "../Config/Settings/GameConfig.h"
#include "Core/Config/Utils/ScaleManager.h"
#include "Core/Data/States/Game/GameplayState.h"

Game::Game()
    : window(sf::VideoMode(GameConfig::getInstance().getWindowWidth(), GameConfig::getInstance().getWindowHeight()), "NFS Console"), renderer(&window), currentState(nullptr)
{
    window.setFramerateLimit(GameConfig::getInstance().getMaxFPS());

    sf::Texture* backgroundTexture = TextureManager::getInstance().loadTexture("Assets/Textures/BackgroundMenu.jpg");

    if (backgroundTexture)
    {
        background.setTexture(*backgroundTexture);
        ScaleManager::getInstance().scaleSpriteToFill(background);
    }
    else { Logger::getInstance().log("Failed to load background texture"); }

    sf::Texture* recordsBackgroundTexture = TextureManager::getInstance().loadTexture("J:/MyIDE/NFS_Console/Assets/Textures/BackgroundRecords.jpg");

    if (recordsBackgroundTexture)
    {
        recordsBackground.setTexture(*recordsBackgroundTexture);
        ScaleManager::getInstance().scaleSpriteToFill(recordsBackground);
    }
    else { Logger::getInstance().log("Failed to load records background texture"); }

    std::vector<std::string> menuTracks =
    {
        "J:/MyIDE/NFS_Console/Assets/Musics/MenuMusic_1.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/MenuMusic_2.wav"
    };

    std::vector<std::string> gameplayTracks =
    {
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_1.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_2.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_3.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_4.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_5.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_6.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_7.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_8.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_9.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_10.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_11.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_12.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_13.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_14.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_15.wav",
        "J:/MyIDE/NFS_Console/Assets/Musics/GameMusic_16.wav",
    };

    MusicManager::getInstance().initializeMenuPlaylist(menuTracks);
    MusicManager::getInstance().initializeGameplayPlaylist(gameplayTracks);

    setState(new MainMenuState(this, &background));
}

void Game::toggleFullscreen()
{
    if (dynamic_cast<GameplayState*>(currentState))
    {
        Logger::getInstance().log("Cannot toggle fullscreen during gameplay!");
        return;
    }

    GameConfig& config = GameConfig::getInstance();
    config.setFullscreen(!config.isFullscreen());

    window.close();

    if (config.isFullscreen()) {
        window.create(sf::VideoMode::getDesktopMode(), "NFS Console", sf::Style::Fullscreen);
        config.setWindowSize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    } else {
        window.create(sf::VideoMode(config.getOriginalWindowWidth(), config.getOriginalWindowHeight()), "NFS Console", sf::Style::Default);
        config.setWindowSize(config.getOriginalWindowWidth(), config.getOriginalWindowHeight());
    }

    window.setFramerateLimit(config.getMaxFPS());
    renderer.setWindow(&window);

    ScaleManager::getInstance().scaleSpriteToFill(background);
    ScaleManager::getInstance().scaleSpriteToFill(recordsBackground);

    Logger::getInstance().log("Toggled fullscreen mode: " + std::string(config.isFullscreen() ? "ON" : "OFF"));
}

Game::~Game()
{
    Logger::getInstance().log("Game destructor called");
    AudioManager::getInstance().stopAllSounds();
    MusicManager::getInstance().stopMusic();
    delete currentState;
    Logger::getInstance().log("Game destructor finished");
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }

            if (currentState) { currentState->processEvents(event); }
        }

        float deltaTime = clock.restart().asSeconds();

        if (currentState)
        {
            currentState->update(deltaTime);
            currentState->render(renderer);
        }
    }
}

void Game::setState(GameState* state)
{
    delete currentState;
    currentState = state;
}

void Game::close()
{
    window.close();
}

sf::Sprite* Game::getBackground()
{
    return &background;
}

sf::Sprite* Game::getRecordsBackground()
{
    return &recordsBackground;
}