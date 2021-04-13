#include "stdafx.h"
#include "Global.h"
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
	skelly->Update(dt);
	
	tickClock += dt;
	if (tickClock >= TICK_DELAY)
	{
		tickClock -= TICK_DELAY;

		if (queuedCommands == 0)
		{
			do {
				command = input->ReadLine(queuedCommands);
			} while (command == Scroll::Command::invalid);

		}
		queuingCommands = (queuedCommands > 1 || queuedCommands < -1);
		queuedCommands -= Utils::signOf(queuedCommands);

		CheckAdjacentsForReaction(skelly->gridPos, command);

		if (!SquareIsFree(skelly->gridPos, command))
		{
			ui->DisplayCommand("Blocked");
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

	window->draw(map.background);
	for (auto entry : objects)
	{
		if (entry.second->sprite != NULL)
		{
			window->draw(*entry.second->sprite);
		}
	}
	window->draw(*skelly);
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
	objects[pos.y * MAP_WIDTH + pos.x] = newObj;
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

bool Scene::SquareIsFree(Vector2i skelPos, Scroll::Command direction)
{
	Vector2i posToCheck = skelPos;
	switch (direction)
	{
	case Scroll::Command::up:
		posToCheck.x -= 1;
		break;
	case Scroll::Command::down:
		posToCheck.x += 1;
		break;
	case Scroll::Command::left:
		posToCheck.y -= 1;
		break;
	case Scroll::Command::right:
		posToCheck.y += 1;
		break;
	default:
		return true;		
	}

	if (posToCheck.x < 0 || posToCheck.x >= MAP_WIDTH || posToCheck.y < 0 || posToCheck.y >= MAP_HEIGHT)
		return false;

	return !map.collisionMap[posToCheck.x][posToCheck.y];
}