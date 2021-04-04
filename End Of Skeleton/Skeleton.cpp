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
    , MOVEMENT_SPEED{ 48 }
    , Journey(0, 0)
    , gridPos(getPosition() / GRID_SQUARE)
{
    setOrigin(27.5f, 40.f); // Temporary

    CreateAnim("Idle", 0, {1}, false);
    CreateAnim("Downward", 0, {0,1,2,1});
    CreateAnim("Leftward", 1, {0,1,2,1});
    CreateAnim("Rightward", 2, {0,1,2,1});
    CreateAnim("Upward", 3, {0,1,2,1});

    SwitchAnim("Downward", false);
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
    //GridPos = getPosition() / GRID_SQUARE;

    // Debug
    if (movement == Vector2f(0,0))
        SwitchAnim("Idle", false);
}

void Skeleton::Reset()
{
    setOrigin(27.5f, 40.f);
    gridPos = Vector2i(getPosition() / GRID_SQUARE);
    Journey = Vector2f(0,0);
    SwitchAnim("Idle");
}

void Skeleton::Wait()
{
    SwitchAnim("Idle");
}

void Skeleton::MoveUp(const int squares)
{
    Journey.y -= squares * GRID_SQUARE;
    SwitchAnim("Upward");
}

void Skeleton::MoveDown(const int squares)
{
    Journey.y += squares * GRID_SQUARE;
    SwitchAnim("Downward");
}

void Skeleton::MoveRight(const int squares)
{
    Journey.x += squares * GRID_SQUARE;
    SwitchAnim("Rightward");
}

void Skeleton::MoveLeft(const int squares)
{
    Journey.x -= squares * GRID_SQUARE;
    SwitchAnim("Leftward");
}