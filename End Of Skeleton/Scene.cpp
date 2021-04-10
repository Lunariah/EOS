#include "stdafx.h"
#include "Global.h"
#include "Scene.h"
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

//Scene::Scene()
//	: 
//{}

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

			switch (command)
			{
			case Scroll::Command::wait:
				skelly->Wait();
				commandString = "Wait";
				break;
			case Scroll::Command::up:
				skelly->MoveUp(queuedCommands);
				commandString = "Up";
				break;
			case Scroll::Command::down:
				skelly->MoveDown(queuedCommands);
				commandString = "Down";
				break;
			case Scroll::Command::left:
				skelly->MoveLeft(queuedCommands);
				commandString = "Left";
				break;
			case Scroll::Command::right:
				skelly->MoveRight(queuedCommands);
				commandString = "Right";
				break;
			case Scroll::Command::eos:
				skelly->Wait();
				commandString = "End of Skeleton";
				break;
			}
			queuingCommands = (queuedCommands > 1 || queuedCommands < -1);
		}
		if (queuingCommands)
			ui->DisplayCommand(commandString + " " + to_string(queuedCommands));
		else
			ui->DisplayCommand(commandString);
		
		queuedCommands -= (queuedCommands >= 0) ? 1 : -1; 
	}
	//window->clear(sf::Color::Black);
	window->draw(map.background);
	window->draw(*skelly);
	//window->draw(second half of background);
	//ui->DrawOn(*window); // Done in Game instead
	//window->display();
}

void Scene::Reload(Vector2i skelPos)
{
	input->Reload();
	skelly->Reset(skelPos);
	queuingCommands = false;
	queuedCommands = 0;
}