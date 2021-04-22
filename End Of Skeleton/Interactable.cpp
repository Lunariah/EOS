#include "stdafx.h"
#include "Interactable.h"
#include <iostream>

using namespace std;
using namespace sf;

void Interactable::UpdateAndDraw(RenderTarget& target, RenderStates states)
{
	if (sprite) {
		sprite->Update();
		target.draw(*sprite, states);
	}
}

// Warps
Warp::Warp(string scene, Vector2i position)
	: nextScene{scene}
	, nextPosition{position}
{}

bool Warp::OnCollision()
{
	cout << "Warping";
	return false;
}



// Doors
Door::Door(string scene, Vector2i position)
	: Warp(scene, position)
{}

void Door::ReactTo(Scroll::Command command)
{
	if (command == Scroll::Command::open)
	{
		cout << "Opening door\n";
	}
}

bool Door::OnCollision()
{
	return true;
}
