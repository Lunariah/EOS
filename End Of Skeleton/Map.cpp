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

	// Fill front layers
	while (layer != tilemap["layers"].end())
	{
		string name = (*layer)["name"];
		if (name == "Player" || name == "player")
			break;

		if (name.compare(1, 8, "ollision") == 0) {
			collisions.clear();
			for(auto obj = (*layer)["data"].begin(); obj != (*layer)["data"].end(); ++obj) 
			{
				collisions.push_back(obj.value());
			}
		}
		else {
			vector<int> newVect; // use something like emplace instead
			for(auto obj = (*layer)["data"].begin(); obj != (*layer)["data"].end(); ++obj)
			{
				newVect.push_back(obj.value());
			}
			frontLayers.push_back(newVect);
		}
		layer++;
	}

	// Fill back layers
	while (layer != tilemap["layers"].end())
	{
		string name = (*layer)["name"];

		if (name.compare(1, 8, "ollision") == 0) {
			collisions.clear();
			for(auto obj = (*layer)["data"].begin(); obj != (*layer)["data"].end(); ++obj) 
			{
				collisions.push_back(obj.value());
			}
		}
		else {
			vector<int> newVect; // use something like emplace instead
			for(auto obj = (*layer)["data"].begin(); obj != (*layer)["data"].end(); ++obj)
			{
				newVect.push_back(obj.value());
			}
			backLayers.push_back(newVect);
		}
		layer++;
	}
}

//GetLayerData(vector<vector<int>>)
