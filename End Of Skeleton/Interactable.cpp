#include "stdafx.h"
#include "Interactable.h"
#include "SceneManager.h"
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
{
	SceneManager::GetInstance()->LoadScene(nextScene);
}

bool Warp::OnCollision()
{
	//cout << "Warping\n";
	SceneManager::GetInstance()->ChangeScene(nextScene, nextPosition);
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
		SceneManager::GetInstance()->ChangeScene(nextScene, nextPosition);
	}
}

bool Door::OnCollision()
{
	return true;
}
