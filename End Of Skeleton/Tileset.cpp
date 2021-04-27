#include "stdafx.h"
#include "Tileset.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;

Tileset::Tileset(const string& path)
{
	ifstream fileStream(path);
	if (!fileStream.is_open())
		throw invalid_argument("Can’t open " + path);
	json file = json::parse(fileStream);

	texture = make_shared<sf::Texture>();
	string texPath = file["image"];
	size_t pathCut = path.find_last_of('/');
	if (pathCut != path.npos)
		texPath = path.substr(0, pathCut + 1) + texPath;
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