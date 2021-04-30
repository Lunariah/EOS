#pragma once
#include "Map.h"
#include "Scroll.h"
#include "Skeleton.h"
#include "UI.h"
#include "Interactable.h"

class Scene
{
 public:
	Scene(std::string &mapPath);
	Scene();
	virtual ~Scene();

	void LoadMap(std::string &mapPath);
	void UpdateAndDraw(float deltaTime, sf::RenderWindow &window, Skeleton &skelly);
	void Reload(sf::Vector2i skelPos, Skeleton &skelly);
	void AddObject(Interactable* newObj, sf::Vector2i pos); // Use with new. Interactable will be deleted by ~Scene
	

 protected:
	Map map;
	std::map<int, Interactable*> objects;
	float tickClock;
	int queuedCommands;
	bool queuingCommands;
	Scroll::Command command;
	std::string commandString;

	void DrawScene(float deltaTime, sf::RenderWindow &window, Skeleton &skelly);
	void CheckAdjacentsForReaction(sf::Vector2i pos, Scroll::Command command);
	bool SquareIsBlocked(sf::Vector2i skelPos, Scroll::Command command, Skeleton& skelly);
	//int GridToIndex(sf::Vector2i gridPos); // Takes a grid position and returns an index to use with the objects map // Implemented in Map instead
};

