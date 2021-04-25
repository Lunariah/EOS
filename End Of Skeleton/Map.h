#pragma once
#include <memory>
#include "Global.h"
#include "Tileset.h"
#include "nlohmann/json.hpp"


class Map
{
 public:
	Map(const std::string &tilemapPath);
	Map(const Map&) = delete; // Can’t copy or move an object containing an sf::Font
	
	void DrawBackground(sf::RenderWindow &window);
	void DrawForeground(sf::RenderWindow &window);

	static inline int GridToIndex(sf::Vector2i gridPos) { return gridPos.y * MAP_WIDTH + gridPos.x; }
	static inline int GridToIndex(int x, int y) { return y * MAP_WIDTH + x; }

	bool collisionMap[MAP_WIDTH][MAP_HEIGHT] = {false};

 private:
	nlohmann::json tilemap;
	Tileset tileset;
	std::vector<sf::VertexArray> backLayers;
	std::vector<sf::VertexArray> frontLayers;
	std::vector<sf::Text> sceneText;
	sf::Font font;

	void ConstructLayer(std::vector<sf::VertexArray> &layerGroup, const nlohmann::detail::iter_impl<nlohmann::json> layerData);
};

