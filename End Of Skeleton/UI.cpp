#include "stdafx.h"
#include "Global.h"
#include "UI.h"
#include <fstream>

using namespace std;
using namespace sf;

UI* UI::instance = nullptr;

UI* UI::GetInstance()
{
	if (instance == nullptr)
		instance = new UI();
	return instance;
}

UI::UI()
	: commandDisplay()
	, permanentUI(vector<Text>())
	, sceneUI(vector<Text>())
	, showGrid{false}
{
	if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
		throw "Couldn’t load font " + FONTS_PATH + "arial.ttf";

	commandDisplay.setFont(font);
	commandDisplay.setCharacterSize(20);
	commandDisplay.setFillColor(Color::White);
	commandDisplay.setPosition(WINDOW_WIDTH - 170, WINDOW_HEIGHT - 40);
	AddText("F5: Reset", Color::White, Vector2f(20, WINDOW_HEIGHT - 40), 20, true);
	AddText("Space: Toggle grid", Color::White, Vector2f(170, WINDOW_HEIGHT - 40), 20, true);

	ConstructGrid();
}

void UI::ConstructGrid()
{
	ifstream texFile(SPRITES_PATH + "Grid.png");
	if (!texFile.is_open())
		throw SPRITES_PATH + "Grid.png is missing";
	texFile.close();


	gridTex.loadFromFile(SPRITES_PATH + "Grid.png");

	int texWidth = gridTex.getSize().x;
	int texHeight = gridTex.getSize().y;

	int gridWidth = WINDOW_WIDTH / texWidth;
	int gridHeight = WINDOW_HEIGHT / texHeight;

	grid = VertexArray(sf::Quads, gridWidth * gridHeight * 4);

	for (int x = 0; x < gridWidth; x++) {
		for (int y = 0; y < gridHeight; y++)
		{
			sf::Vertex* tile = &grid[(y * gridWidth + x) * 4];

			tile[0].position = sf::Vector2f(x * texWidth, y * texHeight);
			tile[1].position = sf::Vector2f((x + 1) * texWidth, y * texHeight);
			tile[2].position = sf::Vector2f((x  + 1) * texWidth, (y + 1) * texHeight);
			tile[3].position = sf::Vector2f(x * texWidth, (y + 1) * texHeight);

			tile[0].texCoords = sf::Vector2f(0, 0);
			tile[1].texCoords = sf::Vector2f(texWidth, 0);
			tile[2].texCoords = sf::Vector2f(texWidth, texHeight);
			tile[3].texCoords = sf::Vector2f(0, texHeight);
		}
	}
}

void UI::AddText(string text, Color colour, Vector2f position, int size, bool permanent)
{
	Text newText(text, font, size);
	newText.setFillColor(colour);
	newText.setPosition(position);

	if (permanent) 
		permanentUI.push_back(newText);
	else 
		sceneUI.push_back(newText);
}

void UI::DisplayCommand(const string &text)
{
	commandDisplay.setString(text);
}

void UI::DrawForeground(RenderWindow& window)
{
	for(Text element : sceneUI)
	{
		window.draw(element);
	}

	for (Text element : permanentUI)
	{
		window.draw(element);
	}

	window.draw(commandDisplay);
}

void UI::DrawBackground(RenderWindow& window)
{
	if (showGrid)
		window.draw(grid, &gridTex);
}

void UI::ClearSceneUI()
{
	sceneUI.clear();
}
