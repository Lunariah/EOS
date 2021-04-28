#pragma once

// Window
inline extern const float GRID_SQUARE = 32.f;
inline extern const int WINDOW_WIDTH = GRID_SQUARE * 18;
inline extern const int WINDOW_HEIGHT = GRID_SQUARE * 19.5;
inline extern const int MAP_OFFSET_X = -1;
inline extern const int MAP_OFFSET_Y = -1;
inline extern const sf::Vector2i MAP_OFFSET(MAP_OFFSET_X, MAP_OFFSET_Y);

// Gameplay
inline extern const float TICK_DELAY = 0.666666667f;
inline extern const float MOVEMENT_SPEED = 48;
inline extern const int MAX_COMMANDS_STACK = 30;

// Files
inline extern const std::string INPUT_PATH = "Scroll of Necromancy.txt";
inline extern const std::string SPRITES_PATH = "Assets/";
inline extern const std::string TILEMAPS_PATH = "Assets/Scenes/";
inline extern const std::string TILESETS_PATH = "Assets/Scenes/";
inline extern const std::string FONTS_PATH = "Assets/";