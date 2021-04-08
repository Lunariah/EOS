#pragma once
#include <memory>

// TODO: Use tilemaps like an adult


class Map
{
 public:
	Map(const std::string &texturePath);
	
	sf::Sprite background;

 private:
	std::shared_ptr<sf::Texture> tex;
};

