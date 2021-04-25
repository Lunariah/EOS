#include "stdafx.h"
#include "SceneManager.h"

using namespace std;
using namespace sf;

SceneManager::SceneManager(RenderWindow* window, Skeleton* skelly, UI* ui, Scroll* input)
	: window{window}
	, skelly{skelly}
	, ui{ui}
	, input{input}
	, currentScene{NULL}
{ }

SceneManager::~SceneManager()
{
	for (pair<string, Scene*> value : loadedScenes) {
		delete value.second;
	}
}

void SceneManager::CreateScene(string name, string mapPath)
{
	//inactiveScenes[name] = mapPath; // Requires default constructor for Map
	inactiveScenes.insert(pair<string, string>(name, mapPath));
}

void SceneManager::LoadScene(string name, Vector2i skelPos, bool autoLoad)
{
	auto search = loadedScenes.find(name);
	if (search != loadedScenes.end())
		currentScene = search->second;
	else
	{
		auto node = inactiveScenes.extract(name);
		loadedScenes.emplace(name, new Scene(window, input, skelly, ui, node.mapped()));
		if (autoLoad)
			currentScene = loadedScenes.find(name)->second;
	}
	skelly->WarpTo(skelPos);
	ui->ClearSceneUI();
}
// Scene would need to keep its mapPath to put the unloaded scene back into inactiveScenes
//void SceneManager::UnloadScene(string name)
//{
//	auto search = loadedScenes.find(name);
//	if (search == loadedScenes.end())
//		throw "Cannot find scene " + name;
//
//	delete loadedScenes[name];
//}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}