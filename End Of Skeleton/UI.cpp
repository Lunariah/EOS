#include "stdafx.h"
#include "Global.h"
#include "UI.h"

using namespace std;
using namespace sf;

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
{
	if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
		throw "Couldn’t load font " + FONTS_PATH + "arial.ttf";

	commandDisplay.setFont(font);
	commandDisplay.setCharacterSize(20);
	commandDisplay.setFillColor(Color::White);
	commandDisplay.setPosition(WINDOW_WIDTH - 170, WINDOW_HEIGHT - 40);
	AddText("F5: Reset", Color::White, Vector2f(20, WINDOW_HEIGHT - 40), 20, true);
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

void UI::DrawOn(RenderWindow& window)
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

void UI::ClearSceneUI()
{
	sceneUI.clear();
}
