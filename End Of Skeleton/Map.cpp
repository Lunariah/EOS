#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <fstream>

// TODO: 
// Replace MAP_HEIGHT and MAP_WIDTH globals by values from the tilemap JSON
// Parse tileset file name from tilemap file

using namespace std;
using json = nlohmann::json;

Map::Map(const string& tilemapPath)
	: tilemap(json::parse(ifstream(tilemapPath)))
	, tileset("Assets/Craftland Demo 32x32 tileset.json") // Can’t access tilemap["tilesets"][0]["source"]. Why?
	, backLayers()
	, frontLayers()
	, sceneText()
	, font()
{
	if (!font.loadFromFile("Assets/arial.ttf")) // Do this properly later
		throw "Couldn’t load font";

	int width = tilemap["width"];
	int height = tilemap["height"];

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
		ConstructLayer(frontLayers, layer);
		layer++;
	}
}

void Map::ConstructLayer(vector<sf::VertexArray> &layerGroup, const nlohmann::detail::iter_impl<json> layerData)
{
	string name = (*layerData)["name"]; // See if I can use compare() directly

	// If it’s the collision layer, record to collision map
	if (name.compare(1, 8, "ollision") == 0) 
	{
		for (int x = 0; x < MAP_WIDTH; x++) {
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				collisionMap[x][y] = ((*layerData)["data"][GridToIndex(x, y)] != 0);
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
			if (obj["visible"]) {
				string text = obj["text"]["text"];
				unsigned int height = obj["height"];
				//sf::Text newText((string)obj["text"]["text"], font, (unsigned int)obj["height"]);
				sf::Text newText(text, font, height);
				newText.setFont(font);
				newText.setPosition(obj["x"], obj["y"]);
				sceneText.push_back(newText);
				//sceneText.emplace_back((string)obj["text"]["text"], font, (unsigned int)obj["height"]);
				//sceneText.back().setPosition(obj["x"], obj["y"]);
			}
		}
		return;
	}

	if ((*layerData)["type"] != "tilelayer")
		return;

	//auto layer = layerGroup.emplace(sf::Quads, MAP_SIZE); // Doesn’t work. Why?
	sf::VertexArray layer(sf::Quads, MAP_SIZE * 4);

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
	layerGroup.push_back(layer);
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
