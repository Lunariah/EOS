#pragma once
class UI
{
 public:
	static UI* GetInstance();

	void AddText(std::string text, sf::Color colour, sf::Vector2f position, int size, bool permanent=false);
	void DisplayCommand(const std::string &command);
	void DrawBackground(sf::RenderWindow &window);
	void DrawForeground(sf::RenderWindow &window);
	void ClearSceneUI();
	void ToggleGrid() { showGrid = !showGrid; }
	void ToggleGrid(bool value) { showGrid = value; }

 private:
	UI();
	static UI* instance;
	sf::Font font;
	sf::Text commandDisplay;
	std::vector<sf::Text> permanentUI;
	std::vector<sf::Text> sceneUI;
	sf::VertexArray grid;
	sf::Texture gridTex;
	bool showGrid;

	void ConstructGrid();
};
