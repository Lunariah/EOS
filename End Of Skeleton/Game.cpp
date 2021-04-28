#include "stdafx.h"
#include "Game.h"
#include "SceneManager.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "End of Skeleton", sf::Style::Titlebar | sf::Style::Close)
    , event()
    , skelly(SPRITES_PATH + "Skeleton.png", 3, 4)
{
    window.setVerticalSyncEnabled(true);

    if(TICK_DELAY * MOVEMENT_SPEED < GRID_SQUARE)
        cout << "Less than one tile is traveled every tick. Please adjust TICK_DELAY and MOVEMENT_SPEED\n";
}

void Game::Run()
{
    //orders.OpenEditor();
    window.setActive();

    Clock clock = Clock();
    float deltaTime;

    SceneManager::GetInstance()->CreateScene("Test", TILEMAPS_PATH + "Labyrinth.json");
    const sf::Vector2i skelSpawn = sf::Vector2i(10,4);
    SceneManager::GetInstance()->LoadScene("Test", skelSpawn);

    // Debug
    Interactable* testObject = new Door("dummy", {2,2});
    Vector2i testPos = {4,11};
    Texture redDot = Texture();
    redDot.loadFromFile(SPRITES_PATH + "dot.png");
    testObject->sprite = AnimatedSprite(redDot, 1, 1);
    SceneManager::GetInstance()->GetCurrentScene()->AddObject(testObject, testPos);

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
                    SceneManager::GetInstance()->GetCurrentScene()->Reload(skelSpawn, skelly);
                    break;
                case Keyboard::Key::Escape:
                    window.close();
                    break;
                }
            }
        }

        window.clear(sf::Color::Black);

        SceneManager::GetInstance()->UpdateAndDrawCurrentScene(deltaTime, window, skelly);
        UI::GetInstance()->DrawOn(window);

        window.display();
    }
}


