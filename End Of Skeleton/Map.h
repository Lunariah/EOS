#pragma once

// TODO: Use tilemaps like an adult


class Map
{
 public:
	Map(const std::string &texturePath);
	
	sf::Sprite background;

 private:
	sf::Texture tex;
};

