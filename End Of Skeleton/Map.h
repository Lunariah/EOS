#pragma once
#include "Tileset.h"
#include <memory>


class Map
{
 public:
	Map(const std::string &tilemapPath);
	Map(const Map&) = delete; // Can�t copy or move an object containing an sf::Font
	
	void DrawBackground(sf::RenderWindow &window);
	void DrawForeground(sf::RenderWindow &window);

	int GridToIndex(sf::Vector2i gridPos) const { return gridPos.y * width + gridPos.x; }
	int GridToIndex(int x, int y) const { return y * width + x; }

	int getWidth() { return width; }
	int getHeight() { return height; }
	bool getCollision(int x, int y) { return collisionMap[y * width + x]; }
	bool getCollision(size_t i) { return collisionMap[i]; }

 private:
	nlohmann::json tilemap;
	Tileset tileset;
	int width;
	int height;
	std::vector<bool> collisionMap;
	std::vector<sf::VertexArray> backLayers;
	std::vector<sf::VertexArray> frontLayers;
	std::vector<sf::Text> sceneText;
	sf::Font font;

	void ConstructLayer(std::vector<sf::VertexArray> &layerGroup, const nlohmann::detail::iter_impl<nlohmann::json> layerData);

};

