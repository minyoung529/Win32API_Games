#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"
#include "Camera.h"
#include "GameObject.h"
#include "BaseCollider.h"

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

void SceneManager::SetLayerName(uint8 index, const wstring& name)
{
	// 기존 데이터 삭제
	const wstring& prevName = m_layerNames[index];
	m_layerIndex.erase(prevName);

	m_layerNames[index] = name;
	m_layerIndex[name] = index;
}

uint8 SceneManager::LayerNameToIndex(const wstring& name)
{
	auto findIt = m_layerIndex.find(name);

	if (findIt == m_layerIndex.end())
	{
		return 0;
	}

	return findIt->second;
}

shared_ptr<class GameObject> SceneManager::Pick(int32 screenX, int32 screenY)
{
	shared_ptr<Camera> camera = GetActiveScene()->GetMainCamera();

	float width = static_cast<float> (g_Engine->GetWindow().width);
	float height = static_cast<float> (g_Engine->GetWindow().height);

	Matrix projMatrix = camera->GetProjMatrix();

	// ViewSpace 
	float viewX = (2.0f * screenX / width - 1.f) / projMatrix(0, 0);
	float viewY = (-2.0f * screenY / height + 1.f) / projMatrix(1, 1);

	// view 역행렬 x 
	Matrix viewMatrix = camera->GetViewMatrix();
	Matrix viewMatrixInv = viewMatrix.Invert();

	// viewspace에서의 ray
	Vec4 rayOrigin = Vec4(0.f, 0.f, 0.f, 0.f);
	Vec4 rayDir = Vec4(viewX, viewY, 1.f, 0.f);

	rayOrigin = XMVector3TransformCoord(rayOrigin, viewMatrixInv);
	rayDir = XMVector3TransformNormal(rayDir, viewMatrixInv);
	rayDir.Normalize();

	auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects();
	float minDistance = FLT_MAX;
	shared_ptr<GameObject> picked;

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetCollider() == nullptr)
			continue;

		float distance = 0.f;
		if (gameObject->GetCollider()->Intersects(rayOrigin, rayDir, OUT distance) == false)
		{
			continue;
		}

		if (distance < minDistance)
		{
			minDistance = distance;
			picked = gameObject;
		}
	}

	return picked;
}