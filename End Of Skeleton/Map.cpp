#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>

// TODO: 
// Replace MAP_HEIGHT and MAP_WIDTH globals by values from the tilemap JSON

using namespace std;
using json = nlohmann::json;

Map::Map(const string& tilemapPath)
	: tilemap([](const string& tilemapPath) {
		ifstream file(tilemapPath);
		if (!file.is_open()) throw invalid_argument("Can’t open " + tilemapPath);
		return json::parse(file);
	} (tilemapPath))

	, tileset([this](const string& tilemapPath) {
		size_t pathCut = tilemapPath.find_last_of('/');
		string tilesetName = tilemap["tilesets"][0]["source"];
		if (pathCut != tilemapPath.npos)
			return tilemapPath.substr(0, pathCut + 1) + tilesetName;
		else
			return tilesetName;
	} (tilemapPath))

	, backLayers()
	, frontLayers()
	, sceneText()
	, font()
{
	if (!font.loadFromFile(FONTS_PATH + "arial.ttf")) // Do this properly later
		throw "Couldn’t load font";

	auto layer = tilemap["layers"].begin();

	// Fill back layers (behind player)
	while (layer != tilemap["layers"].end())
	{
		string name = (*layer)["name"];
		if (name == "Player" || name == "player") {
			layer++;
			break;
		}
		ConstructLayer(backLayers, layer++);
	}

	// Fill front layers (in front of player)
	while (layer != tilemap["layers"].end())
	{
		ConstructLayer(frontLayers, layer++);
	}
}

void Map::ConstructLayer(vector<sf::VertexArray> &layerGroup, const nlohmann::detail::iter_impl<json> layerData)
{
	// If it’s the collision layer, record to collision map
	string name = (*layerData)["name"];
	if (name.compare(1, 8, "ollision") == 0) 
	{
		for (int x = 0; x < MAP_WIDTH; x++) {
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				collisionMap[x][y] = (0 != (*layerData)["data"][GridToIndex(x, y)]);
			}
		}
		return;
	}

	if (!(*layerData)["visible"])
		return;

	// If it’s text, add it to sceneText
	if ((*layerData)["type"] == "objectgroup")
	{
		for (auto obj : (*layerData)["objects"])
		{
			if (obj["visible"]) 
			{
				sf::Text newText((string)obj["text"]["text"], font, obj["height"]);
				newText.setPosition(obj["x"], obj["y"]);

				string color = obj["text"]["color"];
				int a = stoi(color.substr(1, 2), nullptr, 16);
				int r = stoi(color.substr(3, 2), nullptr, 16);
				int g = stoi(color.substr(5, 2), nullptr, 16);
				int b = stoi(color.substr(7, 2), nullptr, 16);
				newText.setFillColor(sf::Color(r, g, b, a));

				sceneText.push_back(newText);
			}
		}
		return;
	}

	// Else, add to tilemap
	if ((*layerData)["type"] != "tilelayer")
		return;

	sf::VertexArray& layer = layerGroup.emplace_back(sf::Quads, MAP_SIZE * 4);

	for (int x = 0; x < MAP_WIDTH; x++) {
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			sf::Vertex* tile = &layer[(GridToIndex(x, y) * 4)];

			int tileType = (*layerData)["data"][GridToIndex(x,y)] - 1;

			if (tileType < 0)
			{
				tile[0].color.a = 0;
				tile[1].color.a = 0;
				tile[2].color.a = 0;
				tile[3].color.a = 0;
			}

			float tWidth = tileset.tileWidth;
			float tHeight = tileset.tileHeight;

			tile[0].position = sf::Vector2f(x * tWidth, y * tHeight);
			tile[1].position = sf::Vector2f((x + 1) * tWidth, y * tHeight);
			tile[2].position = sf::Vector2f((x  + 1) * tWidth, (y + 1) * tHeight);
			tile[3].position = sf::Vector2f(x * tWidth, (y + 1) * tHeight);

			float u = (tileType % tileset.columns) * tWidth;
			float v = (tileType / tileset.columns) * tHeight;

			tile[0].texCoords = sf::Vector2f(u, v);
			tile[1].texCoords = sf::Vector2f(u + tWidth, v);
			tile[2].texCoords = sf::Vector2f(u + tWidth, v + tHeight);
			tile[3].texCoords = sf::Vector2f(u, v + tHeight);
		}
	}
}

void Map::DrawBackground(sf::RenderWindow& window)
{
	for (sf::VertexArray layer : backLayers)
	{
		window.draw(layer, tileset.texture.get());
	}
}

void Map::DrawForeground(sf::RenderWindow& window)
{
	for (sf::VertexArray layer : frontLayers)
	{
		window.draw(layer, tileset.texture.get());
	}

	for (sf::Text text : sceneText)
	{
		window.draw(text);
	}
}
