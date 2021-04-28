#pragma once
#include "Global.h"
#include "Skeleton.h"
#include "Scroll.h"
#include "Scene.h"


class Game
{
 public:
	Game();

	void Run();

 private:
	sf::RenderWindow window;
	sf::Event event;
	Skeleton skelly;
};
