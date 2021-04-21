#include "stdafx.h"
#include "Utils.h"
#include "Scene.h"
#include "Skeleton.h"
#include <iostream>

using namespace std;
using namespace sf;

Scene::Scene(RenderWindow* window, Scroll* input, Skeleton* skelly, UI* ui, const string &mapPath)
	: map(mapPath)
	, window{window}
	, input{input}
	, skelly{skelly}
	, tickClock{0.f}
	, queuedCommands{0}
	, queuingCommands{false}
	, command{}
	, commandString()
	, ui(ui)
{}

Scene::~Scene()
{
	for (pair<int, Interactable*> entry : objects)
	{
		delete entry.second;
	}
}

void Scene::UpdateAndDraw(float dt)
{
	tickClock += dt;
	if (tickClock >= TICK_DELAY)
	{
		tickClock -= TICK_DELAY;

		cout << skelly->gridPos.x << " " << skelly->gridPos.y << endl;

		if (queuedCommands == 0)
		{
			do {
				command = input->ReadLine(queuedCommands);
			} while (command == Scroll::Command::invalid);

		}
		queuingCommands = (queuedCommands > 1 || queuedCommands < -1);
		queuedCommands -= Utils::signOf(queuedCommands);

		CheckAdjacentsForReaction(skelly->gridPos, command);

		if (SquareIsBlocked(skelly->gridPos, command))
		{
			ui->DisplayCommand("Blocked");
			DrawScene(dt);
			return;
		}

		switch (command)
		{
		case Scroll::Command::wait:
			//skelly->Wait();
			commandString = "Wait";
			break;
		case Scroll::Command::up:
			skelly->MoveUp();
			commandString = "Up";
			break;
		case Scroll::Command::down:
			skelly->MoveDown();
			commandString = "Down";
			break;
		case Scroll::Command::left:
			skelly->MoveLeft();
			commandString = "Left";
			break;
		case Scroll::Command::right:
			skelly->MoveRight();
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
			ui->DisplayCommand(commandString + " " + to_string(queuedCommands + 1));
		else
			ui->DisplayCommand(commandString);
	}

	DrawScene(dt);
}

void Scene::DrawScene(float dt)
{
	map.DrawBackground(*window);

	for (auto entry : objects) {
		if (entry.second->sprite)
			window->draw(*entry.second->sprite);
	}

	window->draw(skelly->Update(dt));

	map.DrawForeground(*window);
}

void Scene::Reload(Vector2i skelPos)
{
	input->Reload();
	skelly->Reset(skelPos);
	queuingCommands = false;
	queuedCommands = 0;
}

void Scene::AddObject(Interactable *newObj, Vector2i pos)
{
	objects[GridToIndex(pos)] = newObj;
}

void Scene::CheckAdjacentsForReaction(Vector2i pos, Scroll::Command command)
{
	int index = pos.y * MAP_WIDTH + pos.x;

	auto search = objects.find(index - MAP_HEIGHT);
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

	search = objects.find(index + MAP_HEIGHT);
	if (search != objects.end())
		search->second->ReactTo(command);
}

bool Scene::SquareIsBlocked(Vector2i skelPos, Scroll::Command direction)
{
	Vector2i posToCheck = skelPos;
	switch (direction)
	{
	case Scroll::Command::up:
		posToCheck.y -= 1;
		skelly->MoveUp(0); // Switch to face direction without moving
		break;
	case Scroll::Command::down:
		posToCheck.y += 1;
		skelly->MoveDown(0);
		break;
	case Scroll::Command::left:
		posToCheck.x -= 1;
		skelly->MoveLeft(0);
		break;
	case Scroll::Command::right:
		posToCheck.x += 1;
		skelly->MoveRight(0);
		break;
	default:
		return false;		
	}

	// Check the destination isn’t out of bounds
	if (posToCheck.x < 0 || posToCheck.x >= MAP_WIDTH || posToCheck.y < 0 || posToCheck.y >= MAP_HEIGHT)
		return true;

	// Execute collision script of any Interactable in the way
	int mapIndex = GridToIndex(posToCheck);
	if (objects.find(mapIndex) != objects.end())
	{
		return objects[mapIndex]->OnCollision();
	}

	// Refer to collision map if no object takes precedence
	return map.collisionMap[posToCheck.x][posToCheck.y];
}

inline int Scene::GridToIndex(Vector2i gridPos)
{
	return gridPos.y * MAP_WIDTH + gridPos.x;
}