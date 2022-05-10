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

// �� ���
void SceneManager::RegisterScene(const std::string& sceneName, Scene* scene)
{
	if (scene == nullptr || sceneName.compare("") == 0) return;

	//scene->Init();
	sceneContainer.insert(sceneContainer.end(), pair<string, Scene*>(sceneName, scene));
}

// ���� �� ��ȯ
void SceneManager::ReserveChangeScene(const std::string& sceneName)
{
	auto it = sceneContainer.find(sceneName);

	// ��ϵ� ���鿡 �� ������ �ִٸ�...
	if (it != sceneContainer.end())
	{
		// ���� ���� ���
		reservedScene = it->second;
	}
	else
		reservedScene = nullptr;
}