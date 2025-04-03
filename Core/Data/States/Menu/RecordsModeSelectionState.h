// Core/Data/States/RecordsModeSelectionState.h
#ifndef RECORDSMODESELECTIONSTATE_H
#define RECORDSMODESELECTIONSTATE_H

#include "../GameState.h"
#include "../../../Application/Game.h"

#include <SFML/Graphics.hpp>
#include <vector>

class RecordsModeSelectionState : public GameState
{
public:
    RecordsModeSelectionState(Game* game);
    ~RecordsModeSelectionState();
    void processEvents(sf::Event& event) override;
    void update(float deltaTime) override;
    void render(Renderer& renderer) override;

private:
    enum class MenuOption
    {
        TIME_TRIAL,
        BACK,
        COUNT
    };

    sf::Sprite* background;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    MenuOption selectedOption;
    sf::SoundBuffer selectSoundBuffer;
    sf::Sound selectSound;

    void initializeMenu();
    void updateMenuPositions();
};

#endif //RECORDSMODESELECTIONSTATE_H