#include "stdafx.h"
#include "Interactable.h"

using namespace std;
using namespace sf;

// Abstract class
Interactable::Interactable()
{}

void Interactable::ReactTo(Scroll::Command command)
{}

void Interactable::Collision()
{
}


// Warps
Warp::Warp(string scene, Vector2i position)
	: nextScene{scene}
	, nextPosition{position}
{}

void Warp::Collision()
{
	// SceneManager.load_scene(next_scene)
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

void Door::Collision()
{
}