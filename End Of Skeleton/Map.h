#pragma once
#include <memory>
#include "Global.h"
#include "nlohmann/json.hpp"

// TODO: Use vertex arrays and tilemaps like an adult

extern const int MAP_WIDTH, MAP_HEIGHT;

class Map
{
 public:
	Map(const std::string &texturePath);
	//Map(const std::string &tilemapPath);
	
	void ReadTileMap(const std::string &tilemapPath);

	sf::Sprite background;
	bool collisionMap[MAP_WIDTH][MAP_HEIGHT] = {false};

	nlohmann::json tilemap;
 private:
	std::shared_ptr<sf::Texture> tex;
	std::vector<std::vector<int>> backLayers;
	std::vector<std::vector<int>> frontLayers;
	std::vector<int> collisions; // debug.
	void ParseLayerData(std::vector<std::vector<int>> &layerGroup, nlohmann::detail::iter_impl<nlohmann::json> layer);
};

