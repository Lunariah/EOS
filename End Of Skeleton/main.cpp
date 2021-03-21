#include <stdafx.h>
#include <iostream>
#include "AnimatedSprite.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test", sf::Style::None); // Splashscreen (transparent for now)
    sf::Event event;

    window.setVerticalSyncEnabled(true);

    AnimatedSprite skelly("Assets/Skeleton_trans.png", 3, 4, 4);
    //skelly.setTextureRect(sf::IntRect(24, 64, 24, 32));
    skelly.setPosition(sf::Vector2(50.f, 50.f));
    
    skelly.CreateAnim("Forward", 2, {0,1,2,1}, true);
    skelly.SwitchAnim("Forward", false);

    while (window.isOpen())
    {

        // Event handling
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::LostFocus) // Disapears when out of focus 
                window.close();
        }

        // Clear / Draw / Display cycle
        window.clear(sf::Color::Cyan);

        skelly.Update();
        window.draw(skelly);

        window.display(); // Render frame
    }

    return EXIT_SUCCESS;
}