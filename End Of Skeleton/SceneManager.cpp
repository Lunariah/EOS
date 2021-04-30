#include "stdafx.h"
#include "SceneManager.h"
#include <iostream>

using namespace std;
using namespace sf;

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
	: currentScene{nullptr}
	, firstScene{nullptr}
{ }

SceneManager* SceneManager::GetInstance()
{
	if (instance == nullptr)
		instance = new SceneManager();
	return instance;
}

SceneManager::~SceneManager()
{
	for (pair<string, SceneData> value : scenes) {
		if (value.second.ready)
		delete value.second.scene;
	}
}

void SceneManager::CreateScene(const string &name, const string &mapPath)
{
	scenes.insert(make_pair(name, SceneData(new Scene(), mapPath)));
}

void SceneManager::LoadScene(const string &name)
{
	auto search = scenes.find(name);
	if (search == scenes.end())
		throw invalid_argument("No scene named " + name + " in scene manager");
	if (search->second.ready)
		return;

	search->second.LoadScene();
	cout << "Loading scene " << name << " from " << search->second.mapPath << endl;

	if (firstScene == nullptr)
		firstScene = &search->second;
}

void SceneManager::ChangeScene(const string& name, Vector2i skelPos)
{
	auto search = scenes.find(name);
	if (search == scenes.end())
		throw invalid_argument("No known scene by this name");
	if (search->second.ready == false)
		search->second.LoadScene();

	currentScene = &search->second;
	sceneChange = std::make_pair(currentScene->scene, skelPos);
	
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

	if (currentScene == nullptr)
		return;

	currentScene->scene->UpdateAndDraw(dt, window, skelly);
}

SceneManager::SceneData::SceneData(Scene* scene, string path)
	: scene{scene}
	, mapPath{path}
	, ready{false}
{}

void SceneManager::SceneData::LoadScene()
{
	scene->LoadMap(mapPath);
	ready = true;
}


//void SceneManager::SceneData::UnloadScene()
//{
//	delete scene;
//	scene = new Scene();
//	ready = false;
//}

//void SceneManager::LoadCustomScene(const string &name, Scene* scene)
//{
//	loadedScenes[name] = scene;
//	cout << "Loading scene " << name;
//}
//
//template <class T>
//void SceneManager::LoadCustomScene(T* ptr, const string &name)
//{
//	Scene* scene = dynamic_cast<Scene>(ptr);
//	if (scene == nullptr)
//		throw "Can’t load custom scene";
//	else
//	{
//		loadedScenes[name] = scene;
//		cout << "Loading scene " << name << endl;
//	}
//}

//void SceneManager::UnloadScene(const string &name)
//{
//	auto search = scenes.find(name);
//	if (search != scenes.end())
//		search->second.UnloadScene();
//}