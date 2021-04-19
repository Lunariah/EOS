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

	collumns = file["collumns"];
	tileCount = file["tilecount"];
	tileHeight = file["tileheight"];
	tileWidth = file["tilewidth"];
	margin = file["margin"];
	spacing = file["spacing"];
}

array<sf::Vector2f, 4> Tileset::GetTileUVs(int tileNumber)
{
	array<sf::Vector2f, 4> uvValues;
	
	int u = (tileNumber % collumns) * tileWidth;
	int v = (tileNumber / collumns) * tileHeight;

	uvValues[0] = sf::Vector2f(u, v);
	uvValues[1] = sf::Vector2f(u + tileWidth, v);
	uvValues[2] = sf::Vector2f(u + tileWidth, v + tileHeight);
	uvValues[3] = sf::Vector2f(u, v + tileHeight);

	return uvValues;
}