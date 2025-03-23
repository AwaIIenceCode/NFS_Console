#include "Game.h"

Game::Game()
    : window(sf::VideoMode(GameConfig::getInstance().getWindowWidth(),
                           GameConfig::getInstance().getWindowHeight()), "NFS Console"),
      renderer(window)
{
    window.setFramerateLimit(GameConfig::getInstance().getMaxFPS());

    // Загружаем текстуру фона через TextureManager
    sf::Texture* backgroundTexture = TextureManager::getInstance().loadTexture("J:/MyIDE/NFS_Console/Assets/Textures/background.jpg");
    if (backgroundTexture)
    {
        background.setTexture(*backgroundTexture);

        // Масштабируем спрайт с сохранением пропорций
        float scaleX = static_cast<float>(GameConfig::getInstance().getWindowWidth()) / backgroundTexture->getSize().x;
        float scaleY = static_cast<float>(GameConfig::getInstance().getWindowHeight()) / backgroundTexture->getSize().y;
        float scale = std::min(scaleX, scaleY); // Используем меньший коэффициент
        background.setScale(scale, scale);

        // Центрируем спрайт
        sf::FloatRect bounds = background.getLocalBounds();
        background.setPosition(
            (GameConfig::getInstance().getWindowWidth() - bounds.width * scale) / 2.0f,
            (GameConfig::getInstance().getWindowHeight() - bounds.height * scale) / 2.0f
        );
    }

    else { Logger::getInstance().log("Failed to load background texture, using default color"); }

    // Логируем старт игры
    Logger::getInstance().log("Game started");
}

Game::~Game()
{
    // Логируем закрытие игры
    Logger::getInstance().log("Game closed");
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Game::update()
{
    // Пока пусто
}

void Game::render()
{
    renderer.clear();
    renderer.render(background); // Отрисовываем фон
    renderer.display();
}