#include "stdafx.h"
#include "Game.h"

using namespace sf;
extern const float GRID_SQUARE;

Game::Game()
    : window(sf::VideoMode(640, 690), "End of Skeleton", sf::Style::Titlebar | sf::Style::Close)
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
    orders.OpenEditor(); // Re-enable for build or after reset is implemented

 Init:
    Scene testScene(&window, &orders, &skelly, "Assets/testmap grid - ugly resize.png");
    testScene.running = true;



    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        // Event handling
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Key::F5:
                    orders.Reload();
                    skelly.Reset();
                    goto Init; // Replace with testScene.Restart() once proper scene loading is implemented
                    break;
                case Keyboard::Key::Escape:
                    window.close();
                    break;
                }
            }
        }

        window.clear(sf::Color::Black);

        testScene.UpdateAndDraw(deltaTime);

        window.display();
    }
}


