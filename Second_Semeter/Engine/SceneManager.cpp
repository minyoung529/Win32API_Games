#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update()
{
	if (m_activeScene == nullptr)
		return;

	m_activeScene->Update();
	m_activeScene->LateUpdate();
	m_activeScene->FinalUpdate();
}

void SceneManager::Render()
{
	if (m_activeScene == nullptr)
		return;

	m_activeScene->Render();
}

void SceneManager::LoadScene(wstring sceneName)
{
	if (m_activeScene != nullptr)
		m_activeScene = nullptr;

	auto it = m_sceneContainer.find(sceneName);

	if (it != m_sceneContainer.end())
	{
		m_activeScene = it->second;
		m_activeScene->Start();
	}
}

void SceneManager::RegisterScene(wstring sceneName, shared_ptr<Scene> scene)
{
	if (sceneName.empty() || scene == nullptr)
		return;

	scene->Awake();

	m_sceneContainer.insert(m_sceneContainer.end(), pair<wstring, shared_ptr<Scene>>(sceneName, scene));
}