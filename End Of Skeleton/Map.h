#pragma once

// TODO: Use tilemaps like an adult


class Map
{
 public:
	Map(std::string texturePath);
	
	sf::Sprite background;

 private:
	sf::Texture tex;
};

