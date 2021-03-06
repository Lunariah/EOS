#include "stdafx.h"
#include "Global.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using json = nlohmann::json;

Map::Map()
	: tilemap()
	, tileset()
	, backLayers()
	, frontLayers()
	, sceneText()
	, font()
	, width(0)
	, height(0)
	, collisionMap()
{}

Map::Map(const string& tilemapPath)
	: tilemap([](const string& tilemapPath) {
		ifstream file(tilemapPath);
		if (!file.is_open()) throw invalid_argument("Can?t open " + tilemapPath);
		return json::parse(file);
	} (tilemapPath))

	, tileset([this](const string& tilemapPath) {
		size_t pathCut = tilemapPath.find_last_of('/');
		string tilesetName = tilemap["tilesets"][0]["source"];
		if (pathCut != tilemapPath.npos)
			return tilemapPath.substr(0, pathCut + 1) + tilesetName;
		else
			return tilesetName;
	} (tilemapPath)) // Absolutely horrendous and honestly just here to prove I can use lambdas

	, backLayers()
	, frontLayers()
	, sceneText()
	, font()
	, width(tilemap["width"])
	, height(tilemap["height"])
	, collisionMap(width * height, false)
{
	if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
		throw "Couldn?t load font";

	if (tilemap["tileheight"] != GRID_SQUARE || tilemap["tileheight"] != GRID_SQUARE)
		cout << "Tilemap " + tilemapPath + " uses a different tile size from Global.h?s GRID_SQUARE"; 

	// Fill back layers (behind player)
	nlohmann::json layers = tilemap["layers"];
	json_itr layer_itr = layers.begin();
	while (layer_itr != layers.end())
	{
		string name = (*layer_itr)["name"];
		if (name == "Player" || name == "player") {
			layer_itr++;
			break;
		}
		ConstructLayer(backLayers, layer_itr++);
	}

	// Fill front layers (in front of player)
	while (layer_itr != layers.end())
	{
		ConstructLayer(frontLayers, layer_itr++);
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

void Map::ConstructLayer(vector<sf::VertexArray> &layerGroup, const json_itr layerData)
{
	string name = (*layerData)["name"];
	if (name.compare(1, 8, "ollision") == 0 && (*layerData)["type"] == "tilelayer") 
	{
		ConstructCollisionLayer(layerData);
		return;
	}

	if (!(*layerData)["visible"])
		return;

	if ((*layerData)["type"] == "objectgroup")
	{
		ConstructTextLayer(layerData);
		return;
	}

	if ((*layerData)["type"] == "tilelayer")
	{
		ConstructTileLayer(layerGroup, layerData);
	}
}

void Map::ConstructCollisionLayer(const json_itr layerData)
{
	int mapSize = collisionMap.size();
	for (int i = 0; i < mapSize; i++)
	{
		collisionMap[i] = ((*layerData)["data"][i] != 0);
	}
}

void Map::ConstructTextLayer(const json_itr layerData)
{
	for (auto obj : (*layerData)["objects"])
	{
		if (obj["visible"]) 
		{
			int pixelSize = obj["text"].contains("pixelsize") ? obj["text"]["pixelsize"] : obj["height"];
			sf::Text newText((string)obj["text"]["text"], font, pixelSize);
			newText.setPosition(obj["x"] + MAP_OFFSET_X * GRID_SQUARE, obj["y"] + MAP_OFFSET_Y * GRID_SQUARE);

			if (obj["text"].contains("color"))
			{
				string color = obj["text"]["color"];
				int a, r, g, b;
				if (color.length() == 9) // Turns out Tiled puts the alpha value at the start of the string, but only if it?s != 255
				{
					a = stoi(color.substr(1, 2), nullptr, 16);
					r = stoi(color.substr(3, 2), nullptr, 16);
					g = stoi(color.substr(5, 2), nullptr, 16);
					b = stoi(color.substr(7, 2), nullptr, 16);
				}
				else
				{
					a = 255;
					r = stoi(color.substr(1, 2), nullptr, 16);
					g = stoi(color.substr(3, 2), nullptr, 16);
					b = stoi(color.substr(5, 2), nullptr, 16);
				}
				newText.setFillColor(sf::Color(r, g, b, a));
			}
			else 
				newText.setFillColor(sf::Color::Black);

			sceneText.push_back(newText);
		}
	}
}

void Map::ConstructTileLayer(vector<sf::VertexArray>& layerGroup, const json_itr layerData)
{
	sf::VertexArray& layer = layerGroup.emplace_back(sf::Quads, width * height * 4);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++)
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
			sf::Vector2f offset = sf::Vector2f(MAP_OFFSET_X * tWidth, MAP_OFFSET_Y * tHeight);

			tile[0].position = sf::Vector2f(x * tWidth, y * tHeight) + offset;
			tile[1].position = sf::Vector2f((x + 1) * tWidth, y * tHeight)  + offset;
			tile[2].position = sf::Vector2f((x  + 1) * tWidth, (y + 1) * tHeight) + offset;
			tile[3].position = sf::Vector2f(x * tWidth, (y + 1) * tHeight) + offset;

			float u = (tileType % tileset.columns) * tWidth;
			float v = (tileType / tileset.columns) * tHeight;

			tile[0].texCoords = sf::Vector2f(u, v);
			tile[1].texCoords = sf::Vector2f(u + tWidth, v);
			tile[2].texCoords = sf::Vector2f(u + tWidth, v + tHeight);
			tile[3].texCoords = sf::Vector2f(u, v + tHeight);
		}
	}
}
