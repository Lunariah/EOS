#include "stdafx.h"
#include "UI.h"

using namespace std;
using namespace sf;

UI::UI(string fontPath)
	: commandDisplay()
	, permanentUI(vector<Text>())
	, sceneUI(vector<Text>())
{
	if (!font.loadFromFile(fontPath))
		throw "Couldn’t load font " + fontPath;

	commandDisplay.setFont(font);
	commandDisplay.setCharacterSize(20);
	commandDisplay.setFillColor(Color::White);
	commandDisplay.setPosition(470, 650);
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