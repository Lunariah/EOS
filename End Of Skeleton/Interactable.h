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
	virtual void Reset() {};

	std::optional<AnimatedSprite> sprite;
};


class Warp : public Interactable
{
 public:
	Warp(std::string scene, sf::Vector2i position);
	
	void ReactTo(Scroll::Command command) {}
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

class Obstacle : public Interactable
{
 public:
	Obstacle(const sf::Texture& texture, Scroll::Command key);

	void ReactTo(Scroll::Command command) override;
	bool OnCollision() override { return !open; }
	void Reset() override;

 protected:
	Scroll::Command key;
	bool open;
};

class Chest : public Interactable
{
 public:
	Chest(const sf::Texture& texture, Scroll::Command key, std::string message, sf::Vector2f messagePos);

	void ReactTo(Scroll::Command command) override;
	bool OnCollision() override { return true; }

 protected:
	Scroll::Command key;
	std::string message;
	sf::Vector2f messagePos;
};
