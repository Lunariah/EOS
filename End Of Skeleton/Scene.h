#pragma once

#include "Map.h"
#include "Scroll.h"
#include "Skeleton.h"
#include "UI.h"

class Scene
{
 public:
	Scene(sf::RenderWindow* window, Scroll* input, Skeleton* skelly, UI* ui, const std::string &mapPath);

	void UpdateAndDraw(float deltaTime);
	void Reload(sf::Vector2i skelPos);
	
	Map map; // Switch back to protected when texture bug is fixed

 protected:
	float tickClock;
	int queuedCommands;
	bool queuingCommands;
	Scroll::Command command;
	std::string commandString;

	sf::RenderWindow* window;
	UI* ui;
	Scroll* input;
	Skeleton* skelly;
};

