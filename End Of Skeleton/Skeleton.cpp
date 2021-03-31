#include "stdafx.h"
#include "Skeleton.h"
#include "Utils.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;
extern const float GRID_SQUARE;

Skeleton::Skeleton(const string& textureFile, const int collumns, const int lines) 
    : AnimatedSprite(textureFile, collumns, lines)
    , MOVEMENT_SPEED{ 32 }
    , Journey(0, 0)
{
    CreateAnim("Forward", 2, {0,1,2,1});
    SwitchAnim("Forward", false);
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update(float dt)
{
    AnimatedSprite::Update();

    Vector2f movement = Vector2f(MOVEMENT_SPEED * utils::signOf(Journey.x) * dt
                                , MOVEMENT_SPEED * utils::signOf(Journey.y) * dt);

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
    move(movement);
}

void Skeleton::MoveUp(const int squares)
{
    Journey.y -= squares * GRID_SQUARE;
}

void Skeleton::MoveDown(const int squares)
{
    Journey.y += squares * GRID_SQUARE;
}

void Skeleton::MoveRight(const int squares)
{
    Journey.x += squares * GRID_SQUARE;
}

void Skeleton::MoveLeft(const int squares)
{
    Journey.x -= squares * GRID_SQUARE;
}