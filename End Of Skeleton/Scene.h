#pragma once

#include "Map.h"
#include "Scroll.h"
#include "Skeleton.h"
#include "UI.h"

class Scene
{
 public:
	Scene(sf::RenderWindow* window, Scroll* input, Skeleton* skelly, std::string mapPath);

	void UpdateAndDraw(float deltaTime);
	
	bool running; // Ugly patch, will probably get deleted after implementing the scene loader

 private:
	Map map;
	UI ui; // Also needs to move later on
	float tickClock;
	int queuedCommands;
	bool queuingCommands;
	Scroll::Command command;
	std::string commandString;
	sf::RenderWindow* window;
	Scroll* input;
	Skeleton* skelly;
};

