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

void SceneManager::CreateScene(string name, string mapPath)
{
	//inactiveScenes[name] = mapPath; // Requires default constructor for Map
	inactiveScenes.insert(pair<string, string>(name, mapPath));
}

void SceneManager::LoadScene(string name, Vector2i skelPos)
{
	auto search = loadedScenes.find(name);
	if (search != loadedScenes.end())
		currentScene = &search->second;
	else
	{
		auto node = inactiveScenes.extract(name);
		loadedScenes.insert(pair<string, Scene>(name, Scene(window, input, skelly, ui, node.mapped()))); // Maybe put this in its own thread for good measure
		currentScene = &loadedScenes.find(name)->second;
	}
	skelly->WarpTo(skelPos);
	ui->ClearSceneUI();
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}