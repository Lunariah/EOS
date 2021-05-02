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
    SceneManager* sceneManager = SceneManager::GetInstance();

    const sf::Vector2i skelSpawn = sf::Vector2i(9, 8);

    Texture tree;
    tree.loadFromFile(SPRITES_PATH + "Tree.png");
    Texture chest;
    chest.loadFromFile(SPRITES_PATH + "Chest.png");

    Scene* start = sceneManager->CreateScene("Start", TILEMAPS_PATH + "Start.json");
    Scene* north = sceneManager->CreateScene("North", TILEMAPS_PATH + "North.json");
    Scene* west = sceneManager->CreateScene("West", TILEMAPS_PATH + "West.json");
    Scene* southWest = sceneManager->CreateScene("Southwest", TILEMAPS_PATH + "Southwest.json");
    
    sceneManager->LoadScene("Start");
    sceneManager->LoadScene("North");
    sceneManager->LoadScene("West");
    sceneManager->LoadScene("Southwest");

    start->AddObject(new Warp("North", {9, 18}), {9, 0});
    start->AddObject(new Warp("North", {10, 18}), {10, 0});
    start->AddObject(new Warp("West", {18, 5}), {0, 5});
    start->AddObject(new Warp("West", {18, 6}), {0, 6});
    start->AddObject(new Obstacle(tree, Scroll::Command::cut), {3,8});

    north->AddObject(new Warp("Start", {9, 1}), {9, 19});
    north->AddObject(new Warp("Start", {10, 1}), {10, 19});
    north->AddObject(new Chest(chest, Scroll::Command::open, "#kzut", {316.5, 134.5}), {10, 5});

    west->AddObject(new Warp("Start", {1, 5}), {19, 5});
    west->AddObject(new Warp("Start", {1, 6}), {19, 6});
    west->AddObject(new Warp("Southwest", {4, 1}), {4, 19});
    west->AddObject(new Warp("Southwest", {5, 1}), {5, 19});
    west->AddObject(new Warp("Southwest", {6, 1}), {6, 19});

    southWest->AddObject(new Warp("West", {4, 18}), {4, 0});
    southWest->AddObject(new Warp("West", {5, 18}), {5, 0});
    southWest->AddObject(new Warp("West", {6, 18}), {6, 0});
    southWest->AddObject(new Warp("West", {6, 18}), {7, 0});
    

    sceneManager->LoadScene("Start");
    sceneManager->ChangeScene("Start", skelSpawn);

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
                    sceneManager->Restart(skelSpawn, skelly);
                    Scroll::GetInstance()->Reload();
                    break;
                case Keyboard::Key::Escape:
                    window.close();
                    break;
                }
            }
        }

        window.clear(sf::Color::Black);

        sceneManager->UpdateAndDrawCurrentScene(deltaTime, window, skelly);
        UI::GetInstance()->DrawOn(window);

        window.display();
    }
}


