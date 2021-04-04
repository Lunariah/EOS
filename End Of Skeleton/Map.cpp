#include "stdafx.h"
#include "Map.h"

using namespace std;

Map::Map(string texturePath)
	: tex()
	, background()
{
	tex.loadFromFile(texturePath);
	background.setTexture(tex);
}