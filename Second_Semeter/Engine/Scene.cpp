#include "pch.h"
#include "Scene.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "GameObject.h"
#include "Light.h"

void Scene::Awake()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->FinalUpdate();
	}
}

void Scene::Render()
{
	PushLightData();

	for (const shared_ptr<GameObject>& gameObject : m_gameObjects)
	{
		if (gameObject)
			gameObject->Render();
	}
}

void Scene::PushLightData()
{
	LightParams lightParams = {};

	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject->GetLight() == nullptr)
			continue;

		const LightInfo& lightInfo = gameObject->GetLight()->GetLightInfo();

		lightParams.lights[lightParams.lightCount] = lightInfo;
		lightParams.lightCount++;
	}

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::GLOBAL)->PushGlobalData(&lightParams, sizeof(lightParams));
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
