#include "pch.h"
#include "Scene.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "GameObject.h"
#include "Light.h"
#include "Transform.h"
#include "Camera.h"

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

	// 프로젝션, 뷰를 모두 구한 후 invert 시켜야하기 때문에 가장 나중에
}

void Scene::Render()
{
	PushLightData();
	for (auto& gameObject : m_gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)continue;

		gameObject->GetCamera()->Render();
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
	if (gameObject->GetCamera() != nullptr)
	{
		m_cameras.push_back(gameObject->GetCamera());
	}

	m_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	if (gameObject->GetCamera() != nullptr)
	{
		auto findIt = std::find(m_cameras.begin(), m_cameras.end(), gameObject->GetCamera());

		if (findIt != m_cameras.end())
		{
			m_cameras.erase(findIt);
		}
	}

	auto findIt = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);

	if (findIt != m_gameObjects.end())
	{
		m_gameObjects.erase(findIt);
	}
}

shared_ptr<class Camera> Scene::GetMainCamera()
{
	if (m_cameras.empty())
		return nullptr;

	return m_cameras[0];
}
