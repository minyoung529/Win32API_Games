#include "SceneManager.h"

using namespace std;

CSceneManager::CSceneManager() : m_CurrentScene(nullptr), m_ReservedScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	for (auto it = m_SceneContainer.begin(); it != m_SceneContainer.end(); ++it)
	{
		it->second->Release();
		delete it->second;
	}
}

void CSceneManager::RegisterScene(const std::string& sceneName, CScene* scene)
{
	if (scene == nullptr || sceneName.compare("") == 0)
		return;

	m_SceneContainer.insert(m_SceneContainer.end(), pair<string, CScene*>(sceneName, scene));
}

void CSceneManager::ReserveChangeScene(const std::string& sceneName)
{
	auto it = m_SceneContainer.find(sceneName);

	if (it != m_SceneContainer.end())
	{
		m_ReservedScene = it->second;
	}
	else
		m_ReservedScene = nullptr;
}

void CSceneManager::Init()
{

}

void CSceneManager::Update(float dt)
{
	if (m_ReservedScene)
	{
		if (m_CurrentScene)
			m_CurrentScene->Release();

		if(m_ReservedScene )
			m_ReservedScene->Init();
		m_CurrentScene = m_ReservedScene;

		m_ReservedScene = nullptr;
	}

	if (m_CurrentScene )
		m_CurrentScene->Update(dt);
}

void CSceneManager::Render(HDC hdc, float dt)
{
	if (m_CurrentScene)
		m_CurrentScene->Render(hdc, dt);
}

void CSceneManager::Release()
{

}