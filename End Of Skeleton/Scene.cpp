#include "stdafx.h"
#include "Global.h"
#include "Utils.h"
#include "Scene.h"
#include "Skeleton.h"
#include <iostream>

using namespace std;
using namespace sf;

Scene::Scene(string &mapPath)
	: map(mapPath)
	, tickClock{0.f}
	, queuedCommands{0}
	, queuingCommands{false}
	, command{}
	, commandString()
{}

Scene::Scene()
	: map()
	, tickClock{0.f}
	, queuedCommands{0}
	, queuingCommands{false}
	, command{}
	, commandString()
{}

Scene::~Scene()
{
	for (pair<int, Interactable*> entry : objects)
	{
		delete entry.second;
	}
}

void Scene::LoadMap(string &mapPath)
{
	map.~Map();
	new (&map) Map(mapPath);
}

void Scene::UpdateAndDraw(float dt, RenderWindow& window, Skeleton& skelly)
{
	tickClock += dt;
	if (tickClock >= TICK_DELAY)
	{
		tickClock -= TICK_DELAY;

		//cout << skelly->gridPos.x << " " << skelly->gridPos.y << endl;

		if (queuedCommands == 0)
		{
			do {
				command = Scroll::GetInstance()->ReadLine(queuedCommands);
			} while (command == Scroll::Command::invalid);

		}
		queuingCommands = (queuedCommands > 1 || queuedCommands < -1);
		queuedCommands -= Utils::signOf(queuedCommands);

		CheckAdjacentsForReaction(skelly.gridPos, command);

		if (SquareIsBlocked(skelly.gridPos, command, skelly))
		{
			UI::GetInstance()->DisplayCommand("Blocked");
			DrawScene(dt, window, skelly);
			return;
		}

		switch (command)
		{
		case Scroll::Command::wait:
			//skelly->Wait();
			commandString = "Wait";
			break;
		case Scroll::Command::up:
			skelly.MoveUp();
			commandString = "Up";
			break;
		case Scroll::Command::down:
			skelly.MoveDown();
			commandString = "Down";
			break;
		case Scroll::Command::left:
			skelly.MoveLeft();
			commandString = "Left";
			break;
		case Scroll::Command::right:
			skelly.MoveRight();
			commandString = "Right";
			break;
		case Scroll::Command::open:
			commandString = "Open";
			break;
		case Scroll::Command::eos:
			//skelly->Wait();
			commandString = "End of Skeleton";
			break;
		}
		
		if (queuingCommands)
			UI::GetInstance()->DisplayCommand(commandString + " " + to_string(queuedCommands + 1));
		else
			UI::GetInstance()->DisplayCommand(commandString);
	}

	DrawScene(dt, window, skelly);
}

void Scene::DrawScene(float dt, sf::RenderWindow &window, Skeleton &skelly)
{
	map.DrawBackground(window);

	for (auto entry : objects) {
			entry.second->UpdateAndDraw(window);
	}

	window.draw(skelly.Update(dt));

	map.DrawForeground(window);
}

void Scene::Reload(Vector2i skelPos, Skeleton& skelly)
{
	//Scroll::GetInstance()->Reload();
	skelly.Reset(skelPos);
	queuingCommands = false;
	queuedCommands = 0;

	for (auto entry : objects) {
		entry.second->Reset();
	}
}

void Scene::AddObject(Interactable *newObj, Vector2i pos)
{
	objects[map.GridToIndex(pos)] = newObj;
	if (newObj->sprite)
		newObj->sprite->setPosition((sf::Vector2f)(pos + MAP_OFFSET) * GRID_SQUARE);
}

void Scene::CheckAdjacentsForReaction(Vector2i pos, Scroll::Command command)
{
	int index = pos.y * map.getWidth() + pos.x;

	auto search = objects.find(index - map.getHeight());
	if (search != objects.end())
		search->second->ReactTo(command);
	
	search = objects.find(index - 1);
	if (search != objects.end())
		search->second->ReactTo(command);

	search = objects.find(index);
	if (search != objects.end())
		search->second->ReactTo(command);

	search = objects.find(index + 1);
	if (search != objects.end())
		search->second->ReactTo(command);

	search = objects.find(index + map.getHeight());
	if (search != objects.end())
		search->second->ReactTo(command);
}

bool Scene::SquareIsBlocked(Vector2i skelPos, Scroll::Command direction, Skeleton& skelly)
{
	Vector2i posToCheck = skelPos;
	//cout <<  posToCheck.x << " : " << posToCheck.y << endl;
	switch (direction)
	{
	case Scroll::Command::up:
		posToCheck.y -= 1;
		skelly.MoveUp(0); // Switch to face direction without moving
		break;
	case Scroll::Command::down:
		posToCheck.y += 1;
		skelly.MoveDown(0);
		break;
	case Scroll::Command::left:
		posToCheck.x -= 1;
		skelly.MoveLeft(0);
		break;
	case Scroll::Command::right:
		posToCheck.x += 1;
		skelly.MoveRight(0);
		break;
	default:
		return false;		
	}

	// Check the destination isn’t out of bounds
	if (posToCheck.x < 0 || posToCheck.x >= map.getWidth() || posToCheck.y < 0 || posToCheck.y >= map.getHeight())
		return true;

	// Execute collision script of any Interactable in the way
	int mapIndex = map.GridToIndex(posToCheck);
	if (objects.find(mapIndex) != objects.end())
	{
		return objects[mapIndex]->OnCollision();
	}

	// Refer to collision map if no object takes precedence
	return map.getCollision(posToCheck.x, posToCheck.y);
}

//inline int Scene::GridToIndex(Vector2i gridPos)
//{
//	return gridPos.y * map.width + gridPos.x;
//}