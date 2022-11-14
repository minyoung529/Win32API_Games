#include "pch.h"
#include "Scene.h"
#include "Object.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		// size_t > size()客 烹老
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			if (m_vecObj[i][j])
			{
				delete m_vecObj[i][j];
			}
		}
	}
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		// size_t > size()客 烹老
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			m_vecObj[i][j]->Update();
		}
	}
}

void Scene::Render(HDC hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		// size_t > size()客 烹老
		for (size_t j = 0; j < m_vecObj[i].size(); j++)
		{
			m_vecObj[i][j]->Render(hdc);
		}
	}
}