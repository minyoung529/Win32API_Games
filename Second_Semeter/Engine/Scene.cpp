#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	for (const shared_ptr<GameObject> gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject> gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject> gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject> gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->LateUpdate();
	}
}

void Scene::Render()
{
	for (const shared_ptr<GameObject> gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Render();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	m_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto findIt = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);

	if (findIt != m_gameObjects.end())
	{
		m_gameObjects.erase(findIt);
	}
}
