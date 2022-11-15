#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Scene.h"
#include "Transform.h"
#include "SceneManager.h"
#include "PlayerController.h"
#include "Camera.h"
#include "CameraController.h"

void Game::Init(const WindowInfo& window)
{
	m_sampleScene = make_shared<Scene>();
	g_Engine->Init(window);

	shared_ptr<GameObject> gameObj = make_shared<GameObject>();
	gameObj->Init();

	gameObj->AddComponent(make_shared<Transform>());
	shared_ptr<Transform> transform = gameObj->GetTransform();
	transform->SetLocalPosition(Vec3::Zero);
	transform->SetLocalScale(Vec3::One * 10.f);

	vector<Vertex> vec(3);
	vec[0].pos = Vec3(0.0f, 0.5f, 0.5f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[0].uv = Vec2(0.5f, 0.f);
	vec[1].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[1].uv = Vec2(1.f, 1.f);
	vec[2].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	vec[2].uv = Vec2(0.f, 1.f);

	vector<uint32> indexVec;
	{
		indexVec.push_back(0);
		indexVec.push_back(1);
		indexVec.push_back(2);
	}

	shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();

	{
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->Init(vec, indexVec);

		meshRenderer->SetMesh(mesh);
	}

	{
		shared_ptr<Shader> shader = make_shared<Shader>();
		shared_ptr<Texture> texture = make_shared<Texture>();
		shader->Init(L"..\\Engine\\Default.hlsli");
		texture->Init(L"..\\Resources\\Texture\\Illidan.png");

		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(0, texture);
		material->SetFloat(0, 0.3f);
		material->SetFloat(1, -0.4f);
		material->SetFloat(2, 0.2f);

		meshRenderer->SetMaterial(material);
	}

	gameObj->AddComponent(meshRenderer);
	gameObj->AddComponent(make_shared<PlayerController>());

	m_sampleScene->AddGameObject(gameObj);

#pragma region Camera
	shared_ptr<GameObject> camera = make_shared<GameObject>();
	camera->AddComponent(make_shared<Transform>());
	camera->AddComponent(make_shared<Camera>());
	camera->AddComponent(make_shared<CameraController>());
	camera->GetTransform()->SetLocalPosition(Vec3(0.f, 10.f, -10.f));

	m_sampleScene->AddGameObject(camera);
#pragma endregion

	GET_SINGLE(SceneManager)->RegisterScene(L"SampleScene", m_sampleScene);
	GET_SINGLE(SceneManager)->LoadScene(L"SampleScene");
}

void Game::Update()
{
	g_Engine->Update();
}

void Game::Render()
{
	g_Engine->Render();
}

void Game::Release()
{
}
