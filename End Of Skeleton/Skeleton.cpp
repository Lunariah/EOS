#include "stdafx.h"
#include "Global.h"
#include "Skeleton.h"
#include "Utils.h"
#include "Global.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

//Skeleton::Skeleton(const Texture& texture, const int collumns, const int lines)
//    : Skeleton()
//{
//    //texture(texture);
//}

Skeleton::Skeleton(const int collumns, const int lines)
    : sprite(collumns, lines)
    , texture()
    , Journey{0, 0}
    , gridPos{0, 0}
{}

Skeleton::Skeleton(const string& texturePath, const int collumns, const int lines)
    : Skeleton(collumns, lines)
{
    texture.loadFromFile(texturePath);
    sprite = AnimatedSprite(texture, collumns, lines);

    sprite.setOrigin(27.5f, 40.f);

    sprite.CreateAnim("Idle", 0, {1}, false);
    sprite.CreateAnim("Downward", 0, {0,1,2,1});
    sprite.CreateAnim("Leftward", 1, {0,1,2,1});
    sprite.CreateAnim("Upward", 3, {0,1,2,1});
    sprite.CreateAnim("Rightward", 2, {0,1,2,1});

    sprite.SwitchAnim("Idle", false);
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update(float dt)
{
    sprite.Update();

    Vector2f movement = Vector2f(MOVEMENT_SPEED * Utils::signOf(Journey.x) * dt
                                , MOVEMENT_SPEED * Utils::signOf(Journey.y) * dt);

    if (abs(Journey.x) < abs(movement.x))
    {
        if (Journey.x == 0)
            movement.x = 0;
        else
            movement.x = Journey.x;
    }

    if (abs(Journey.y) < abs(movement.y))
    {
        if (Journey.y == 0)
            movement.y = 0;
        else 
            movement.y = Journey.y;
    }

    Journey -= movement;
    sprite.move(movement);
    gridPos = Vector2i(sprite.getPosition() / GRID_SQUARE); // Override setPosition instead

    // Debug
    if (movement == Vector2f(0,0))
        sprite.FreezeAnim(1);
}

void Skeleton::Reset(Vector2i position)
{
    SetGridPosition(position);
    Journey = Vector2f(0,0);
    sprite.SwitchAnim("Idle");
}

void Skeleton::SetGridPosition(sf::Vector2i pos)
{
    //gridPos = pos; // Done in Update anyway
    sprite.setPosition(Vector2f(GRID_SQUARE / 2 + (pos.x * GRID_SQUARE), GRID_SQUARE / 2 + (pos.y * GRID_SQUARE)));
}


// COMMANDS

void Skeleton::Wait()
{
    sprite.FreezeAnim(1);
}

void Skeleton::MoveUp(const int squares)
{
    Journey.y -= squares * GRID_SQUARE;
    sprite.SwitchAnim("Upward");
}

void Skeleton::MoveDown(const int squares)
{
    Journey.y += squares * GRID_SQUARE;
    sprite.SwitchAnim("Downward");
}

void Skeleton::MoveRight(const int squares)
{
    Journey.x += squares * GRID_SQUARE;
    sprite.SwitchAnim("Rightward");
}

void Skeleton::MoveLeft(const int squares)
{
    Journey.x -= squares * GRID_SQUARE;
    sprite.SwitchAnim("Leftward");
}