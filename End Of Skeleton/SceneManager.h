#pragma once
#include "Skeleton.h"
#include "Map.h"
#include "Scene.h"

class SceneManager
{
 public:
	static SceneManager* GetInstance();
	SceneManager(SceneManager &other) = delete;
	~SceneManager();

	void CreateScene(const std::string &name, const std::string &mapPath);
	void LoadScene(const std::string &name);
	void ChangeScene(const std::string &name, sf::Vector2i skelPos);
	void UnloadScene(const std::string &name);
	void UpdateAndDrawCurrentScene(float deltaTime, sf::RenderWindow &window, Skeleton& skelly);
	Scene* GetCurrentScene();

	void operator=(const SceneManager &) = delete;

 private:
	SceneManager();
	static SceneManager* instance;

	std::unordered_map<std::string, std::string> scenes; // name, mapPath
	std::unordered_map<std::string, Scene*> loadedScenes;
	Scene* currentScene;
	Scene* firstScene;
	std::optional<std::pair<Scene*, sf::Vector2i>> sceneChange;
};

