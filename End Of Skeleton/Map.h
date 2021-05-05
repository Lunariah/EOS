#pragma once
#include "Tileset.h"
#include <memory>

using json_itr = nlohmann::detail::iter_impl<nlohmann::json>;

class Map
{
 public:
	Map(const std::string &tilemapPath);
	Map();
	Map(const Map&) = delete; // Can’t copy or move an object containing an sf::Font
	
	void DrawBackground(sf::RenderWindow &window);
	void DrawForeground(sf::RenderWindow &window);

	inline int GridToIndex(sf::Vector2i gridPos) const { return gridPos.y * width + gridPos.x; }
	inline int GridToIndex(int x, int y) const { return y * width + x; }

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	bool getCollision(int x, int y) const { return collisionMap[y * width + x]; }
	bool getCollision(size_t i) const { return collisionMap[i]; }

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

	void ConstructLayer(std::vector<sf::VertexArray> &layerGroup, const json_itr layerData);
	void ConstructCollisionLayer(const json_itr layerData);
	void ConstructTextLayer(const json_itr layerData);
	void ConstructTileLayer(std::vector<sf::VertexArray> &layerGroup, const json_itr layerData);
};
