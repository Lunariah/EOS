#include "stdafx.h"
#include "Tileset.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;

Tileset::Tileset(const string& path)
{
	ifstream fileStream(path);
	json file = json::parse(fileStream);

	texture = make_shared<sf::Texture>();
	string texPath = file["image"];
	texPath = "Assets/" + texPath; // TODO: parse from path
	texture->loadFromFile(texPath);

	tileWidth = file["tilewidth"];
	columns = file["columns"];
	tileCount = file["tilecount"];
	tileHeight = file["tileheight"];
	margin = file["margin"];
	spacing = file["spacing"];
}

// Deprecated. I just do it directly in Map
array<sf::Vector2f, 4> Tileset::GetTileUVs(int tileNumber)
{
	array<sf::Vector2f, 4> uvValues;
	
	int u = (tileNumber % columns) * tileWidth;
	int v = (tileNumber / columns) * tileHeight;

	uvValues[0] = sf::Vector2f(u, v);
	uvValues[1] = sf::Vector2f(u + tileWidth, v);
	uvValues[2] = sf::Vector2f(u + tileWidth, v + tileHeight);
	uvValues[3] = sf::Vector2f(u, v + tileHeight);

	return uvValues;
}