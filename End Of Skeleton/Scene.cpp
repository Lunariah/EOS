#include "stdafx.h"
#include "Scene.h"
#include <iostream>

using namespace std;
using namespace sf;

const float TICK_DELAY = 0.666666667f;
Scene::Scene(RenderWindow* window, Scroll* input, Skeleton* skelly, string mapPath)
	: map(mapPath)
	, window{window}
	, input{input}
	, skelly{skelly}
	, running{false}
	, tickClock{0.f}
	, queuedCommands{0}
	, queuingCommands{false}
	, command{}
	, commandString()
	, ui("Assets/arial.ttf")
{
	ui.AddText("F5: Reset", Color::White, Vector2f(20, 650), 20, true);

	skelly->setPosition(sf::Vector2f(335.5f, 16.f));
}

void Scene::UpdateAndDraw(float dt)
{
	skelly->Update(dt);
	
	tickClock += dt;
	if (running && tickClock >= TICK_DELAY)
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
				running = false;
				commandString = "End of Skeleton";
				break;
			}
			queuingCommands = (queuedCommands > 1 || queuedCommands < -1);
		}
		if (queuingCommands)
			ui.DisplayCommand(commandString + " " + to_string(queuedCommands));
		else
			ui.DisplayCommand(commandString);
		
		queuedCommands -= (queuedCommands >= 0) ? 1 : -1; 
	}
	//window->clear(sf::Color::Black);
	window->draw(map.background);
	window->draw(*skelly);
	ui.DrawOn(*window);
	//window->display();
}