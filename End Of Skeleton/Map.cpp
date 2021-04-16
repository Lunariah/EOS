#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

Map::Map(const string& texturePath)
{
	tex = make_shared<sf::Texture>();
	tex->loadFromFile(texturePath);
	background = sf::Sprite(*tex);
}

//Map::Map(const string& tilemapPath)
//{
//
//}

void Map::ReadTileMap(const string& tilemapPath)
{
	ifstream ifs(tilemapPath);
	tilemap = json::parse(ifs);

	int width = tilemap["width"];
	int height = tilemap["height"];


	auto layer = tilemap["layers"].begin();

	// Fill back layers (behind player)
	while (layer != tilemap["layers"].end())
	{
		string name = (*layer)["name"];
		if (name == "Player" || name == "player")
			break;

		ParseLayerData(backLayers, layer);
		layer++;
	}

	// Fill front layers (in front of player)
	while (layer != tilemap["layers"].end())
	{
		ParseLayerData(frontLayers, layer);
		layer++;
	}
}

void Map::ParseLayerData(vector<vector<int>> &layerGroup, nlohmann::detail::iter_impl<json> layer)
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
		vector<int> newVect;
		newVect.reserve((int)(*layer)["width"] * (int)(*layer)["height"]);

		for(auto obj = (*layer)["data"].begin(); obj != (*layer)["data"].end(); ++obj)
		{
			newVect.push_back(obj.value());
		}
		layerGroup.push_back(newVect);
	}
}
