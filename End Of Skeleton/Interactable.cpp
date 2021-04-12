#include "stdafx.h"
#include "Interactable.h"
#include <iostream>

using namespace std;
using namespace sf;

// Abstract class
Interactable::Interactable()
{}

void Interactable::ReactTo(Scroll::Command command)
{}

void Interactable::OnCollision()
{
}


// Warps
Warp::Warp(string scene, Vector2i position)
	: nextScene{scene}
	, nextPosition{position}
{}

void Warp::OnCollision()
{
	cout << "Warping";
}


// Doors
Door::Door(string scene, Vector2i position)
	: Warp(scene, position)
{}

void Door::ReactTo(Scroll::Command command)
{
	if (command == Scroll::Command::open)
	{
		cout << "Opening door";
	}
}

void Door::OnCollision()
{
}