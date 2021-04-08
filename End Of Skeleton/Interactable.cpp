#include "stdafx.h"
#include "Interactable.h"

using namespace std;
using namespace sf;

// Abstract class
Interactable::Interactable()
{}

void Interactable::ReactTo(Scroll::Command command)
{}

bool Interactable::Collision()
{
	return false;
}


// Warps
Warp::Warp(string scene, Vector2i position)
	: nextScene{scene}
	, nextPosition{position}
{}

bool Warp::Collision()
{
	// SceneManager.load_scene(next_scene)
	return true;
}


// Doors
Door::Door(string scene, Vector2i position)
	: Warp(scene, position)
{}

void Door::ReactTo(Scroll::Command command)
{
	if (command == Scroll::Command::open)
	{
		// load scene
	}
}

bool Door::Collision()
{
	return true;
}