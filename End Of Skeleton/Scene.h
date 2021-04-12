#pragma once

#include "Map.h"
#include "Scroll.h"
#include "Skeleton.h"
#include "UI.h"
#include "Interactable.h"

class Scene
{
 public:
	Scene(sf::RenderWindow* window, Scroll* input, Skeleton* skelly, UI* ui, const std::string &mapPath);
	~Scene();

	void UpdateAndDraw(float deltaTime);
	void Reload(sf::Vector2i skelPos);
	void AddObject(Interactable* newObj, sf::Vector2i pos); // Use with new, Interactable will be deleted by ~Scene
	

 protected:
	Map map;
	std::map<int, Interactable*> objects;
	float tickClock;
	int queuedCommands;
	bool queuingCommands;
	Scroll::Command command;
	std::string commandString;

	sf::RenderWindow* window;
	UI* ui;
	Scroll* input;
	Skeleton* skelly;

	void CheckAdjacentsForReaction(sf::Vector2i pos, Scroll::Command command);
	bool SquareIsFree(sf::Vector2i skelPos, Scroll::Command command);
};

