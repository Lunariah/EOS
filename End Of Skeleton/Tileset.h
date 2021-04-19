#pragma once
class Tileset
{
 public:
	Tileset(const std::string& path);

	std::array<sf::Vector2f, 4> GetTileUVs(int tileNumber);

	std::shared_ptr<sf::Texture> texture;
	// Some of this could probably be private.
	int collumns;
	int tileCount;
	float tileHeight, tileWidth;
	float margin; // Unimplemented
	float spacing; // Unimplemented
};

