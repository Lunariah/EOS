#pragma once

#include "Map.h"
#include "Scroll.h"
#include "Skeleton.h"

class Scene
{
 public:
	Scene(sf::RenderWindow* window, Scroll* input, Skeleton* skelly, std::string mapPath);

	void UpdateAndDraw(float deltaTime);
	
	bool running; // Ugly patch, will probably get deleted after implementing the scene loader

 private:
	Map map;
	float tickClock;
	int queuedCommands;
	Scroll::Command command;
	sf::RenderWindow* window;
	Scroll* input;
	Skeleton* skelly;
};

