#include "stdafx.h"
#include "Global.h"
#include "Game.h"
#include "SceneManager.h"
#include <string>

using namespace sf;
using namespace std;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "End of Skeleton", sf::Style::Titlebar | sf::Style::Close)
    , event()
    , skelly("Assets/Skeleton_new.png", 3, 4)
    , orders("Scroll of Necromancy.txt")
{
    window.setVerticalSyncEnabled(true);
}

void Game::Run()
{
    //orders.OpenEditor();
    window.setActive();

    Clock clock = Clock();
    float deltaTime;

    UI ui("Assets/arial.ttf");
    ui.AddText("F5: Reset", Color::White, Vector2f(20, 650), 20, true);

    SceneManager sceneManager(&window, &skelly, &ui, &orders);
    sceneManager.CreateScene("Test", "Assets/testmap grid - ugly resize.png");

    // Debug
    Texture texDebug = Texture();
    texDebug.loadFromFile("Assets/testmap grid - ugly resize.png");
    Sprite bgDebug = Sprite(texDebug);
    bgDebug.setPosition(0,0);
    Scene sceneDebug = Scene(&window, &orders, &skelly, &ui, "Assets/testmap grid - ugly resize.png");

    const sf::Vector2i skelSpawn = sf::Vector2i(10,2);
    sceneManager.LoadScene("Test", skelSpawn);
    sceneManager.GetCurrentScene()->AddObject(Door("dummy", {4,11}), {1,1});


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
                    sceneManager.currentScene->Reload(skelSpawn);
                    break;
                case Keyboard::Key::Escape:
                    window.close();
                    break;
                }
            }
        }

        window.clear(sf::Color::Black);

        sceneManager.currentScene->UpdateAndDraw(deltaTime);
        //sceneDebug.UpdateAndDraw(deltaTime);
        //window.draw(bgDebug);
        ui.DrawOn(window);

        window.display();
    }
}


