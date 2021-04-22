#pragma once
#include "Scroll.h"
#include "AnimatedSprite.h"
#include <optional>

class Interactable
{
 public:

	virtual void ReactTo(Scroll::Command command) = 0; // Does something when a command is executed next to it
	virtual bool OnCollision() = 0; // Process collision and returns false if the object can be walked trough
	virtual void UpdateAndDraw(sf::RenderTarget& target, sf::RenderStates states=sf::RenderStates::Default);

	std::optional<AnimatedSprite> sprite;
};


class Warp : public Interactable
{
 public:
	Warp(std::string scene, sf::Vector2i position);
	
	//void ReactTo(Scroll::Command command) {}
	bool OnCollision() override;
 
 protected:
	std::string nextScene;
	sf::Vector2i nextPosition;
};


class Door : public Warp
{
 public:
	Door(std::string scene, sf::Vector2i position);

	void ReactTo(Scroll::Command command) override;
	bool OnCollision() override;
};
