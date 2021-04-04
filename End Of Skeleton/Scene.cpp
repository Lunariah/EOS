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
	, command{}
{
	skelly->setPosition(sf::Vector2f(335.5f, 16.f));
}

void Scene::UpdateAndDraw(float dt)
{
	skelly->Update(dt);
	
	tickClock += dt;
	if (running && tickClock >= TICK_DELAY)
	{
		tickClock -= TICK_DELAY;
		cout << "----------\nQueued commands: " << queuedCommands << endl;

		if (queuedCommands == 0)
		{
			do {
				command = input->ReadLine(queuedCommands);
			} while (command == Scroll::Command::invalid);

			switch (command)
			{
			case Scroll::Command::wait:
				skelly->Wait();
				cout << "Wait" << endl;
				break;
			case Scroll::Command::up:
				skelly->MoveUp(queuedCommands);
				cout << "Up" << endl;
				break;
			case Scroll::Command::down:
				skelly->MoveDown(queuedCommands);
				cout << "Down" << endl;
				break;
			case Scroll::Command::left:
				skelly->MoveLeft(queuedCommands);
				cout << "Left" << endl;
				break;
			case Scroll::Command::right:
				skelly->MoveRight(queuedCommands);
				cout << "Right" << endl;
				break;
			case Scroll::Command::eos:
				skelly->Wait();
				running = false;
				cout << "End of Skeleton";
				break;
			}

		}
		// TODO: Display current command
		queuedCommands--;
	}
	//window->clear(sf::Color::Black);
	window->draw(map.background);
	window->draw(*skelly);
	//window->display();
}