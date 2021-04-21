#pragma once
#include <memory>
#include "Global.h"
#include "Tileset.h"
#include "nlohmann/json.hpp"

// TODO: Use vertex arrays and tilemaps like an adult

class Map
{
 public:
	Map(const std::string &texturePath);
	//Map(const std::string &tilemapPath);
	
	void DrawBackground(sf::RenderWindow &window);
	void DrawForeground(sf::RenderWindow &window);
	static inline int GridToIndex(sf::Vector2i gridPos) { return gridPos.y * MAP_WIDTH + gridPos.x; }
	static inline int GridToIndex(int x, int y) { return y * MAP_WIDTH + x; }

	//sf::Sprite background;
	bool collisionMap[MAP_WIDTH][MAP_HEIGHT] = {false};


 private:
	std::string tsName;
	nlohmann::json tilemap;
	Tileset tileset;
	//std::shared_ptr<sf::Texture> tex;
	std::vector<std::array<int, MAP_SIZE>> backLayers_int;
	std::vector<std::array<int, MAP_SIZE>> frontLayers_int;
	std::vector<int> collisions; // debug.

	std::vector<sf::VertexArray> backLayers;
	std::vector<sf::VertexArray> frontLayers;

	void ParseLayerData(std::vector<std::array<int, MAP_SIZE>> &layerGroup, nlohmann::detail::iter_impl<nlohmann::json> layer);
	void ConstructLayer(std::vector<sf::VertexArray> &layerGroup, const nlohmann::detail::iter_impl<nlohmann::json> layerData);
};

