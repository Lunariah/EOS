#pragma once
#include "Skeleton.h"
#include "Map.h"
#include "Scene.h"

class SceneManager
{
 public:
	SceneManager(sf::RenderWindow *window, Skeleton *skelly, UI *ui, Scroll *input);
	~SceneManager();

	void CreateScene(std::string name, std::string mapPath);
	void LoadScene(std::string name, sf::Vector2i skelPos, bool autoLoad=true);
	//void UnloadScene(std::string name);
	Scene* GetCurrentScene();
	Scene* currentScene;

 private:
	std::unordered_map<std::string, std::string> inactiveScenes;
	std::unordered_map<std::string, Scene*> loadedScenes;
	sf::RenderWindow* window;
	Skeleton* skelly;
	UI* ui;
	Scroll* input;
};

