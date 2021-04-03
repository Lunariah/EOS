#include "stdafx.h"
#include "Game.h"

using namespace sf;
extern const float GRID_SQUARE;

Game::Game()
    : window(sf::VideoMode(960, 960), "Test", sf::Style::Titlebar | sf::Style::Close)
    , event()
    , skelly("Assets/Skeleton_new.png", 3, 4)
    , orders("Scroll of Necromancy.txt")
{
    window.setVerticalSyncEnabled(true);

}

void Game::Run()
{
    Clock clock = Clock();
    float deltaTime;

    Texture background_tex;
    if (!background_tex.loadFromFile("Assets/testmap grid - ugly resize.png"))
        throw "Failed to load background map";
    Sprite background_sp;
    background_sp.setTexture(background_tex);

    skelly.setPosition(sf::Vector2f(335.5f, 16.f));
    skelly.Journey = sf::Vector2f(0, 10.f * GRID_SQUARE);


    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        // Event handling
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear / Draw / Display cycle
        window.clear(sf::Color::Black);

        window.draw(background_sp);
        skelly.Update(deltaTime);
        window.draw(skelly);

        window.display(); // Render frame
    }
}


