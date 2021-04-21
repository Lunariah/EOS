#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

Map::Map(const string& tilemapPath)
	: tilemap(json::parse(ifstream(tilemapPath)))
	//, tsName([this](){string name; name = tilemap["tilesets"][0]["source"]; return name;} ())
	, tileset("Assets/Craftland Demo tileset.json") // Can’t access tilemap["tilesets"][0]["source"] for some reason
	, backLayers_int()
	, frontLayers_int()
	, collisions()
	, backLayers()
{
	//tsName = tilemap["tilesets"][0]["source"];
	//const string folder = "Assets/"; // TODO: parse directly from tilemapPath
	//tsName = "Assets/Craftland Demo tileset.json";

	int width = tilemap["width"];
	int height = tilemap["height"];

	auto layer = tilemap["layers"].begin();

	// Fill back layers (behind player)
	while (layer != tilemap["layers"].end())
	{
		string name = (*layer)["name"];
		if (name == "Player" || name == "player")
			break;

		ConstructLayer(backLayers, layer);
		layer++;
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
	string name = (*layerData)["name"];

	// If it’s the collision layer, record to collision map
	if (name.compare(1, 8, "ollision") == 0) 
	{
		collisions.clear();
		for(auto obj = (*layerData)["data"].begin(); obj != (*layerData)["data"].end(); ++obj) 
		{
			collisions.push_back(obj.value());
		}
		return;
	}

	// Otherwise, construct vertex array

	//auto layer = layerGroup.emplace(sf::Quads, MAP_SIZE); // Doesn’t work. Why?
	sf::VertexArray layer(sf::Quads, MAP_SIZE * 4);

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			int tileType = (*layerData)["data"][GridToIndex(x,y)];

			sf::Vertex* tile = &layer[(GridToIndex(x, y) * 4)];

			float tWidth = tileset.tileWidth;
			float tHeight = tileset.tileHeight;

			tile[0].position = sf::Vector2f(x * tWidth, y * tHeight);
			tile[1].position = sf::Vector2f((x + 1) * tWidth, y * tHeight);
			tile[2].position = sf::Vector2f((x  + 1) * tWidth, (y + 1) * tHeight);
			tile[3].position = sf::Vector2f(x * tWidth, (y + 1) * tHeight);

			int u = (tileType % tileset.columns) * tWidth;
			int v = (tileType / tileset.columns) * tHeight;

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
}


// To Delete
void Map::ParseLayerData(vector<array<int, MAP_SIZE>> &layerGroup, nlohmann::detail::iter_impl<json> layer)
{
	string name = (*layer)["name"];

	if (name.compare(1, 8, "ollision") == 0) 
	{
		collisions.clear();
		for(auto obj = (*layer)["data"].begin(); obj != (*layer)["data"].end(); ++obj) 
		{
			collisions.push_back(obj.value());
		}
	}
	else 
	{
		layerGroup.push_back((*layer)["data"]);
	}
}
