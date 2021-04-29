#include "stdafx.h"
#include "SceneManager.h"
#include <iostream>

using namespace std;
using namespace sf;

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
	: currentScene{nullptr}
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

void SceneManager::LoadScene(const string &name)
{
	auto search = loadedScenes.find(name);
	string filePath = scenes.find(name)->second;
	if (search == loadedScenes.end())
	{
		loadedScenes[name] = new Scene(filePath);
		cout << "Loading scene " << name << " from " << filePath << endl; 
	}
}

void SceneManager::UnloadScene(const string &name)
{
	delete loadedScenes.extract(name).mapped();
}

void SceneManager::ChangeScene(const string& name, Vector2i skelPos)
{
	sceneChange = std::make_pair(loadedScenes[name], skelPos);
	currentScene = loadedScenes[name];
	
	// Scene will be changed on next UpdateAndDraw, when we have access to the Skeleton 
}

void SceneManager::UpdateAndDrawCurrentScene(float dt, sf::RenderWindow &window, Skeleton& skelly)
{
	if (sceneChange)
	{
		//currentScene = sceneChange->first;
		skelly.WarpTo(sceneChange->second);
		sceneChange.reset();
		UI::GetInstance()->ClearSceneUI(); 
	}

	if (currentScene != nullptr)
		currentScene->UpdateAndDraw(dt, window, skelly);
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}
