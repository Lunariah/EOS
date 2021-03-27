#include "stdafx.h"
#include "Skeleton.h"

using namespace std;
using namespace sf;
extern const float GRID_SQUARE;

Skeleton::Skeleton(const string& textureFile, const int collumns, const int lines) 
    : AnimatedSprite(textureFile, collumns, lines)
{
    
}

Skeleton::~Skeleton()
{
}

void Skeleton::MoveUp(const int squares)
{
    move(0.f, squares * -GRID_SQUARE);
}

void Skeleton::MoveDown(const int squares)
{
    move(0.f, squares * GRID_SQUARE);
}

void Skeleton::MoveRight(const int squares)
{
    move(squares * GRID_SQUARE, 0.f);
}

void Skeleton::MoveLeft(const int squares)
{
    move(squares * -GRID_SQUARE, 0.f);
}