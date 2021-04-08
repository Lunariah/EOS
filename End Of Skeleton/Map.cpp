#include "stdafx.h"
#include "Map.h"

using namespace std;

Map::Map(const string& texturePath)
	: tex()
{
	tex.loadFromFile(texturePath);
	background = sf::Sprite(tex);
}