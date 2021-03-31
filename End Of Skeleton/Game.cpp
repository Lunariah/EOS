#include "stdafx.h"
#include "Game.h"

using namespace sf;

Game::Game()
    : window(sf::VideoMode(800, 600), "Test", sf::Style::Titlebar | sf::Style::Close)
    , event()
    , skelly("Assets/Skeleton_trans.png", 3, 4)
    , orders("Scroll of Necromancy.txt")
{
    window.setVerticalSyncEnabled(true);

}

void Game::Run()
{
    Clock clock = Clock();
    float deltaTime;

    skelly.setPosition(sf::Vector2f(50.f, 50.f));
    skelly.Journey = sf::Vector2f(64, 128);


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

        skelly.Update(deltaTime);
        window.draw(skelly);

        window.display(); // Render frame
    }
}


