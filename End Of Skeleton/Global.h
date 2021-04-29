#pragma once

// Window
static constexpr float GRID_SQUARE = 32.f;
static constexpr int WINDOW_WIDTH = GRID_SQUARE * 18;
static constexpr int WINDOW_HEIGHT = GRID_SQUARE * 19.5;
static constexpr int MAP_OFFSET_X = -1;
static constexpr int MAP_OFFSET_Y = -1;
static const sf::Vector2i MAP_OFFSET(MAP_OFFSET_X, MAP_OFFSET_Y);

// Gameplay
static constexpr float TICK_DELAY = 0.666666667f;
static constexpr float MOVEMENT_SPEED = 48;
static constexpr int MAX_COMMANDS_STACK = 30;

// Files
static const std::string INPUT_PATH = "Scroll of Necromancy.txt";
static const std::string SPRITES_PATH = "Assets/";
static const std::string TILEMAPS_PATH = "Assets/Scenes/";
static const std::string TILESETS_PATH = "Assets/Scenes/";
static const std::string FONTS_PATH = "Assets/";