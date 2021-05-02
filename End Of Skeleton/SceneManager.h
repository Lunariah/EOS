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
	//void AddScene(Scene* newScene, const std::string &name);
	void LoadScene(const std::string &name);
	//template <class T> void LoadCustomScene(T* ptr, const string &name);
	void ChangeScene(const std::string &name, sf::Vector2i skelPos);
	//void UnloadScene(const std::string &name);
	void UpdateAndDrawCurrentScene(float deltaTime, sf::RenderWindow &window, Skeleton& skelly);
	void Restart(sf::Vector2i skelPos, Skeleton skelly);
	Scene* GetCurrentScene() { return currentScene->scene; }

	void operator=(const SceneManager &) = delete;

 private:
	SceneManager();
	static SceneManager* instance;

	struct SceneData
	{
		SceneData(Scene* scene, std::string path);
		SceneData() = default;
		void LoadScene();
		//void UnloadScene();
		Scene* scene;
		bool ready;
		std::string mapPath;
	};

	std::unordered_map<std::string, SceneData> scenes; // name, mapPath
	SceneData* currentScene;
	SceneData* firstScene;
	std::optional<std::pair<Scene*, sf::Vector2i>> sceneChange;

};

