#pragma once
class Tileset
{
 public:
	Tileset(const std::string& path);
	Tileset() = default;

	std::array<sf::Vector2f, 4> GetTileUVs(int tileNumber); // Unused

	std::shared_ptr<sf::Texture> texture;

	// TODO: setters
	int columns;
	int tileCount;
	float tileHeight, tileWidth;

 private:
	float margin; // Unimplemented
	float spacing; // Unimplemented
};

