#pragma once
#include "Global.h"
#include "Tileset.h"
#include <memory>


class Map
{
 public:
	Map(const std::string &tilemapPath);
	Map(const Map&) = delete; // Can’t copy or move an object containing an sf::Font
	
	void DrawBackground(sf::RenderWindow &window);
	void DrawForeground(sf::RenderWindow &window);

	inline int GridToIndex(sf::Vector2i gridPos) const { return gridPos.y * width + gridPos.x; }
	inline int GridToIndex(int x, int y) const { return y * width + x; }

 private:
	nlohmann::json tilemap;
	Tileset tileset;
	std::vector<sf::VertexArray> backLayers;
	std::vector<sf::VertexArray> frontLayers;
	std::vector<sf::Text> sceneText;
	sf::Font font;

	void ConstructLayer(std::vector<sf::VertexArray> &layerGroup, const nlohmann::detail::iter_impl<nlohmann::json> layerData);

 public:
	int width;
	int height;
	std::vector<bool> collisionMap;
};

