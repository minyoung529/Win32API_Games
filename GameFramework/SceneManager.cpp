#include "pch.h"
#include "SceneManager.h"
#include "Scene_Start.h"

SceneManager::SceneManager()
	: m_pCurScene(nullptr)
	, m_arrScene{}
{
}

SceneManager::~SceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (m_arrScene[i])
		{
			delete m_arrScene[i];
			m_arrScene[i] = nullptr;
		}
	}
}

void SceneManager::Init()
{
	m_arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start();
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start_Scene");

	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void SceneManager::Update()
{
	m_pCurScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	m_pCurScene->Render(hdc);
}