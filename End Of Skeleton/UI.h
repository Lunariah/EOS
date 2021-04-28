#pragma once
class UI
{
 public:
	static UI* GetInstance();

	void AddText(std::string text, sf::Color colour, sf::Vector2f position, int size, bool permanent=false);
	void DisplayCommand(const std::string &command);
	void DrawOn(sf::RenderWindow &window);
	void ClearSceneUI();

 private:
	UI();
	static UI* instance;
	sf::Font font;
	sf::Text commandDisplay;
	std::vector<sf::Text> permanentUI;
	std::vector<sf::Text> sceneUI;
};
