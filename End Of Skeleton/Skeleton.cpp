#include "stdafx.h"
#include "Skeleton.h"

Skeleton::Skeleton()
{
    texture.loadFromFile("Assets/Skeleton_trans.png");     
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(24, 64, 24, 32));
    sprite.setPosition(sf::Vector2(50.f, 50.f));
}

Skeleton::~Skeleton()
{
}