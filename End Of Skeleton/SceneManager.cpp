#include "stdafx.h"
#include "SceneManager.h"

using namespace std;
using namespace sf;

SceneManager::SceneManager()
	: currentScene{NULL}
{ }

SceneManager* SceneManager::GetInstance()
{
	if (instance == nullptr)
		instance = new SceneManager();
	return instance;
}

SceneManager::~SceneManager()
{
	for (pair<string, Scene*> value : loadedScenes) {
		delete value.second;
	}
}

void SceneManager::CreateScene(const string &name, const string &mapPath)
{
	scenes.insert(pair<string, string>(name, mapPath));
}

void SceneManager::LoadScene(const string &name, Vector2i skelPos, bool startNow)
{
	auto search = loadedScenes.find(name);
	string filePath = scenes.find(name)->second;
	loadedScenes.try_emplace(name, filePath);

	//if (search == loadedScenes.end())
		//loadedScenes.insert(make_pair(name, Scene(scenes.find(name)->second)));

	if (startNow)
		sceneChange = std::make_pair(search->second, skelPos);
}

void SceneManager::UnloadScene(const string &name)
{
	delete loadedScenes.extract(name).mapped();
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::UpdateAndDrawCurrentScene(float dt, sf::RenderWindow &window, Skeleton& skelly)
{
	if (sceneChange)
	{
		currentScene = sceneChange->first;
		skelly.WarpTo(sceneChange->second);
		sceneChange.reset();
		UI::GetInstance()->ClearSceneUI();
	}

	currentScene->UpdateAndDraw(dt, window, skelly);
}