#include "stdafx.h"
#include "Global.h"

// Window
const float GRID_SQUARE = 32.f;
const int WINDOW_WIDTH = GRID_SQUARE * 18;
const int WINDOW_HEIGHT = GRID_SQUARE * 19.5;
const int MAP_OFFSET_X = -1;
const int MAP_OFFSET_Y = -1;
const sf::Vector2i MAP_OFFSET(MAP_OFFSET_X, MAP_OFFSET_Y);

// Gameplay
const float TICK_DELAY = 0.666666667f;
const float MOVEMENT_SPEED = 48;
const int MAX_COMMANDS_STACK = 30;

// Files
const std::string INPUT_PATH = "Scroll of Necromancy.txt";
const std::string SPRITES_PATH = "Assets/";
const std::string TILEMAPS_PATH = "Assets/Scenes/";
const std::string TILESETS_PATH = "Assets/Scenes/";
const std::string FONTS_PATH = "Assets/";