#pragma once
#include "Scroll.h"

class Interactable
{
 public:
	Interactable();

	virtual void ReactTo(Scroll::Command command); // Does something when a command is executed next to it
	virtual void Collision(); // Process collision and returns false if the object can be walked trough
};


class Warp : Interactable
{
 public:
	Warp(std::string scene, sf::Vector2i position);
	
	void ReactTo(Scroll::Command command) {}
	void Collision();
 
 protected:
	std::string nextScene;
	sf::Vector2i nextPosition;
};


class Door : Warp
{
 public:
	Door(std::string scene, sf::Vector2i position);

	void ReactTo(Scroll::Command command);
	void Collision();
};
