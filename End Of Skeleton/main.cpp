#include <stdafx.h>
#include <iostream>
#include "AnimatedSprite.h"
#include "Orders.h"

extern const float GRID_SQUARE = 32.f;

int main()
{
    // TEST ZONE

    Orders scroll("scroll.txt");

    ////////////

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;

    window.setVerticalSyncEnabled(true);

    AnimatedSprite skelly("Assets/Skeleton_trans.png", 3, 4);
    //skelly.setTextureRect(sf::IntRect(24, 64, 24, 32));
    skelly.setPosition(sf::Vector2f(50.f, 50.f));
    
    skelly.CreateAnim("Forward", 2, {0,1,2,1});
    skelly.SwitchAnim("Forward", false);

    while (window.isOpen())
    {

        // Event handling
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear / Draw / Display cycle
        window.clear(sf::Color::Black);

        skelly.Update();
        window.draw(skelly);

        window.display(); // Render frame
    }

    return EXIT_SUCCESS;
}