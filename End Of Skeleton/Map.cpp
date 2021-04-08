#include "stdafx.h"
#include "Map.h"

using namespace std;

Map::Map(const string& texturePath)
{
	tex = make_shared<sf::Texture>();
	tex->loadFromFile(texturePath);
	background = sf::Sprite(*tex);
}