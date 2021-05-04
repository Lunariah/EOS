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


//////////////////////////////////////
// Warps
//////////////////////////////////////
Warp::Warp(string scene, Vector2i position)
	: nextScene{scene}
	, nextPosition{position}
{
	SceneManager::GetInstance()->LoadScene(nextScene);
}

bool Warp::OnCollision()
{
	SceneManager::GetInstance()->ChangeScene(nextScene, nextPosition);
	return false;
}


//////////////////////////////////////
// Doors
//////////////////////////////////////
Door::Door(string scene, Vector2i position)
	: Warp(scene, position)
{}

void Door::ReactTo(Scroll::Command command)
{
	if (command == Scroll::Command::open)
		SceneManager::GetInstance()->ChangeScene(nextScene, nextPosition);
}

bool Door::OnCollision()
{
	return true;
}


//////////////////////////////////////
// Obstacles
//////////////////////////////////////
Obstacle::Obstacle(const Texture& texture, Scroll::Command key)
	: key{key}
	, open{false}
{
	sprite = AnimatedSprite(texture, 2, 1);
	sprite->CreateStill("Closed", 0, 0);
	sprite->CreateStill("Open", 1, 0);
	sprite->SwitchAnim("Closed");
}

void Obstacle::ReactTo(Scroll::Command command)
{
	if (!open && command == key) 
	{
		open = true;
		sprite->SwitchAnim("Open");
	}
}

void Obstacle::Reset()
{
	sprite->SwitchAnim("Closed");
	open = false;
}


//////////////////////////////////////
// Chests
//////////////////////////////////////
Chest::Chest(const Texture& texture, Scroll::Command key, string message, Vector2f messagePos)
	: key{key}
	, messagePos{messagePos}
	, message(message)
{
	sprite = AnimatedSprite(texture, 1, 1);
	sprite->CreateStill("Closed", 0, 0);
	sprite->SwitchAnim("Closed");
}

void Chest::ReactTo(Scroll::Command command)
{
	if (command == key)
		UI::GetInstance()->AddText(message, sf::Color::Black, messagePos, 16);
}