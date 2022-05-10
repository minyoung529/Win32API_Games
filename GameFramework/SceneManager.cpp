#include "SceneManager.h"
using namespace std;

SceneManager::SceneManager()
{
	reservedScene = nullptr;
	currentScene = nullptr;
}

SceneManager::~SceneManager()
{
	for (auto it = sceneContainer.begin(); it != sceneContainer.end(); ++it)
	{
		it->second->Release();
		delete it->second;
	}
}

void SceneManager::Init()
{

}

void SceneManager::Update(float deltaTime)
{
	if (reservedScene)
	{
		if (currentScene)
			currentScene->Release();

		reservedScene->Init();

		currentScene = reservedScene;
		reservedScene = nullptr;
	}

	if (currentScene)
		currentScene->Update(deltaTime);
}

void SceneManager::Render(HDC hdc, float deltaTime)
{
	if (currentScene)
		currentScene->Render(hdc, deltaTime);
}

void SceneManager::Release()
{
}

// 씬 등록
void SceneManager::RegisterScene(const std::string& sceneName, Scene* scene)
{
	if (scene == nullptr || sceneName.compare("") == 0) return;

	//scene->Init();
	sceneContainer.insert(sceneContainer.end(), pair<string, Scene*>(sceneName, scene));
}

// 예약 씬 전환
void SceneManager::ReserveChangeScene(const std::string& sceneName)
{
	auto it = sceneContainer.find(sceneName);

	// 등록된 씬들에 씬 네임이 있다면...
	if (it != sceneContainer.end())
	{
		// 예약 씬에 등록
		reservedScene = it->second;
	}
	else
		reservedScene = nullptr;
}