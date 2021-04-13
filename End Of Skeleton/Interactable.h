#pragma once
#include "Scroll.h"
#include "AnimatedSprite.h"
#include <optional>

class Interactable
{
 public:

	virtual void ReactTo(Scroll::Command command) = 0; // Does something when a command is executed next to it
	virtual void OnCollision() = 0; // Process collision and returns false if the object can be walked trough

	std::optional<AnimatedSprite> sprite;
};


class Warp : public Interactable
{
 public:
	Warp(std::string scene, sf::Vector2i position);
	
	//void ReactTo(Scroll::Command command) {}
	void OnCollision() override;
 
 protected:
	std::string nextScene;
	sf::Vector2i nextPosition;
};


class Door : public Warp
{
 public:
	Door(std::string scene, sf::Vector2i position);

	void ReactTo(Scroll::Command command) override;
	void OnCollision() override;
};
