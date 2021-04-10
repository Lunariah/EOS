#pragma once
#include <memory>
#include "Global.h"

// TODO: Use vertex arrays and tilemaps like an adult

extern const int MAP_WIDTH, MAP_HEIGHT;

class Map
{
 public:
	Map(const std::string &texturePath);
	
	sf::Sprite background;
	bool collisionMap[MAP_WIDTH][MAP_HEIGHT] = {false};

 private:
	std::shared_ptr<sf::Texture> tex;
};

