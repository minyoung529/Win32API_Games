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
#include "Resources.h"

void Game::Init(const WindowInfo& window)
{
	m_sampleScene = make_shared<Scene>();
	g_Engine->Init(window);


#pragma region Camera
	shared_ptr<GameObject> camera = make_shared<GameObject>();
	camera->AddComponent(make_shared<Transform>());
	camera->AddComponent(make_shared<Camera>());
	camera->AddComponent(make_shared<CameraController>());
	camera->GetTransform()->SetLocalPosition(Vec3(0.f, 10.f, -20.f));

	m_sampleScene->AddGameObject(camera);
#pragma endregion

#pragma region Cube
	{
		shared_ptr<GameObject> cube = make_shared<GameObject>();
		cube->AddComponent(make_shared<Transform>());
		cube->GetTransform()->SetLocalScale(Vec3::One * 10.f);
		cube->GetTransform()->SetLocalPosition(Vec3(5.f, 10.f, 10.f));

		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadCubeMesh();
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
			meshRenderer->SetMaterial(material);
		}

		cube->AddComponent(meshRenderer);
		m_sampleScene->AddGameObject(cube);
	}
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
