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

	// ��������, �並 ��� ���� �� invert ���Ѿ��ϱ� ������ ���� ���߿�
}

void Scene::Render()
{
	PushLightData();

	// SwapChain Group �ʱ�ȭ
	int8 backIndex = g_Engine->GetSwapChain()->GetBackBufferIndex();
	g_Engine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->ClearRenderTargetView(backIndex);
	
	// Deferred Group �ʱ�ȭ
	g_Engine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->ClearRenderTargetView();
	
	// Deferred OMSet
	g_Engine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->OMSetRenderTargets();
	
	shared_ptr<Camera> mainCamera = m_cameras[0];	// mainCam
	mainCamera->SortGameObject();
	mainCamera->Render_Deferred();
	
	// Swapchain OMSet
	g_Engine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTargets(1, backIndex);
	
	mainCamera->Render_Forward();

	// ���� ����,
	// �� �ܿ��� ��� forward rendering
	
	for (auto& camera : m_cameras)
	{
		if (camera == mainCamera)
			continue;

		// Swapchain OMSet
		g_Engine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTargets(1, backIndex);

		camera->SortGameObject();
		camera->Render_Forward();
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
