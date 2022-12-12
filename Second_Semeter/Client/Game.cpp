#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "PlayerController.h"
#include "Camera.h"
#include "CameraController.h"
#include "Resources.h"
#include "Light.h"

void Game::Init(const WindowInfo& window)
{
	m_SampleScene = make_shared<Scene>();

	g_Engine->Init(window);

#pragma region Layer
	GET_SINGLE(SceneManager)->SetLayerName(0, L"Default");
	GET_SINGLE(SceneManager)->SetLayerName(1, L"UI");
#pragma endregion 

#pragma region Camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<Camera>());
		camera->AddComponent(make_shared<CameraController>());
		camera->GetTransform()->SetLocalPosition(Vec3(0.f, 10.f, -20.f));
		uint8 layerIndex = GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI");
		camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, true);
		m_SampleScene->AddGameObject(camera);
	}
#pragma endregion

#pragma region UI Camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<Camera>());
		camera->GetTransform()->SetLocalPosition(Vec3::Zero);
		uint8 layerIndex = GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI");
		camera->GetCamera()->SetCullingMaskAll();							// 전부 OFF
		camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, false);	// UI만 보이도록 한다.
		camera->GetCamera()->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
		m_SampleScene->AddGameObject(camera);
	}
#pragma endregion

#pragma region Skybox
	{
		shared_ptr<GameObject> skybox = make_shared<GameObject>();
		skybox->AddComponent(make_shared<Transform>());
		skybox->SetCheckFrustum(false);

		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadSphereMesh();
			meshRenderer->SetMesh(mesh);
		}
		{
			shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Skybox");
			shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Skybox", L"..\\Resources\\Texture\\Skybox.jpg");

			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}

		skybox->AddComponent(meshRenderer);
		m_SampleScene->AddGameObject(skybox);
	}
#pragma endregion

#pragma region UI Test
	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->SetLayerIndex(GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI"));
		sphere->AddComponent(make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3::One * 100.f);
		sphere->GetTransform()->SetLocalPosition(Vec3(0.0f, 0.0f, 500.0f));

		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadQuadMesh();
			meshRenderer->SetMesh(mesh);
		}
		{
			shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Default");
			shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Illidan", L"..\\Resources\\Texture\\Illidan.png");

			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}

		sphere->AddComponent(meshRenderer);
		m_SampleScene->AddGameObject(sphere);
	}
#pragma endregion


#pragma region Cube
	{
		shared_ptr<GameObject> cube = make_shared<GameObject>();
		cube->AddComponent(make_shared<Transform>());
		cube->GetTransform()->SetLocalScale(Vec3(10.0f, 10.0f, 10.0f));
		cube->GetTransform()->SetLocalPosition(Vec3(5.0f, 10.0f, 10.0f));

		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadCubeMesh();
			meshRenderer->SetMesh(mesh);
			{
				shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Default");
				shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Metal", L"..\\Resources\\Texture\\Metal.jpg");
				shared_ptr<Texture> texture2 = GET_SINGLE(Resources)->Load<Texture>(L"Metal_Normal", L"..\\Resources\\Texture\\Metal_Normal.jpg");

				shared_ptr<Material> material = make_shared<Material>();
				material->SetShader(shader);
				material->SetTexture(0, texture);
				material->SetTexture(1, texture2);
				meshRenderer->SetMaterial(material);
			}

			cube->AddComponent(meshRenderer);
			m_SampleScene->AddGameObject(cube);
		}
#pragma endregion

#pragma region Sphere
		{
			shared_ptr<GameObject> sphere = make_shared<GameObject>();
			sphere->AddComponent(make_shared<Transform>());
			sphere->GetTransform()->SetLocalScale(Vec3(10.0f, 10.0f, 10.0f));
			sphere->GetTransform()->SetLocalPosition(Vec3(-10.0f, 10.0f, 10.0f));

			shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
			{
				shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadSphereMesh();
				meshRenderer->SetMesh(mesh);
			}
			{
				shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Default");
				shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Illidan", L"..\\Resources\\Texture\\Illidan.png");

				shared_ptr<Material> material = make_shared<Material>();
				material->SetShader(shader);
				material->SetTexture(0, texture);
				meshRenderer->SetMaterial(material);
			}

			sphere->AddComponent(meshRenderer);
			//m_SampleScene->AddGameObject(sphere);
		}
#pragma endregion

#pragma region Plane
		{
			shared_ptr<GameObject> sphere = make_shared<GameObject>();
			sphere->AddComponent(make_shared<Transform>());
			sphere->GetTransform()->SetLocalScale(Vec3(1.0f, 1.0f, 1.0f));
			sphere->GetTransform()->SetLocalPosition(Vec3(0.0f, 0.0f, 0.0f));

			shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
			{
				shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadPlaneMesh(100.0f, 100.0f, 50, 50);
				meshRenderer->SetMesh(mesh);
			}
			{
				shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Default");
				shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Illidan", L"..\\Resources\\Texture\\Illidan.png");

				shared_ptr<Material> material = make_shared<Material>();
				material->SetShader(shader);
				material->SetTexture(0, texture);
				meshRenderer->SetMaterial(material);
			}

			sphere->AddComponent(meshRenderer);
			//m_SampleScene->AddGameObject(sphere);
		}
#pragma endregion

#pragma region Model
		{
			shared_ptr<GameObject> sphere = make_shared<GameObject>();
			sphere->AddComponent(make_shared<Transform>());
			sphere->GetTransform()->SetLocalScale(Vec3(1.0f, 1.0f, 1.0f));
			sphere->GetTransform()->SetLocalPosition(Vec3(0.0f, 5.0f, 0.0f));

			shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
			{
				shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadMeshFile(L"..\\Resources\\Models\\skull.txt", L"skull");
				meshRenderer->SetMesh(mesh);
			}
			{
				shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Default");
				shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Illidan", L"..\\Resources\\Texture\\Illidan.png");

				shared_ptr<Material> material = make_shared<Material>();
				material->SetShader(shader);
				material->SetTexture(0, texture);
				meshRenderer->SetMaterial(material);
			}

			sphere->AddComponent(meshRenderer);
			m_SampleScene->AddGameObject(sphere);
		}
#pragma endregion

#pragma region Green Directional Light
		{
			shared_ptr<GameObject> light = make_shared<GameObject>();
			light->AddComponent(make_shared<Transform>());
			light->AddComponent(make_shared<Light>());
			light->GetLight()->SetLightDirection(Vec3(1.f, -1.f, 0.f));
			light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
			light->GetLight()->SetDiffuse(Vec3(0.5f, 0.5f, 0.5f));
			light->GetLight()->SetAmbient(Vec3::Zero);
			light->GetLight()->SetSpecular(Vec3::One * 0.3f);

			m_SampleScene->AddGameObject(light);
		}
#pragma endregion

#pragma region Red Point Light
		{
			shared_ptr<GameObject> light = make_shared<GameObject>();
			light->AddComponent(make_shared<Transform>());
			light->GetTransform()->SetLocalPosition(Vec3::One * 30.f);
			light->AddComponent(make_shared<Light>());
			light->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
			light->GetLight()->SetDiffuse(Vec3::Right);
			light->GetLight()->SetAmbient(Vec3::Zero);
			light->GetLight()->SetSpecular(Vec3::One * 0.3f);
			light->GetLight()->SetLightRange(100.f);

			//m_SampleScene->AddGameObject(light);
		}
#pragma endregion

#pragma region Blue Spot Light
		{
			shared_ptr<GameObject> light = make_shared<GameObject>();
			light->AddComponent(make_shared<Transform>());
			light->GetTransform()->SetLocalPosition(Vec3(-100.f, 0.f, 0.f));

			light->AddComponent(make_shared<Light>());
			light->GetLight()->SetLightType(LIGHT_TYPE::SPOT_LIGHT);
			light->GetLight()->SetLightDirection(Vec3(1.f, 0.f, 0.f));
			light->GetLight()->SetDiffuse(Vec3(0.f, 0.1f, 1.0f));
			light->GetLight()->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			light->GetLight()->SetSpecular(Vec3(0.3f, 0.3f, 0.3f));
			light->GetLight()->SetLightRange(100.f);
			light->GetLight()->SetLightAngle(XM_PI / 4);

			//m_SampleScene->AddGameObject(light);
		}
#pragma endregion

		// 씬 등록(저장하기)
		GET_SINGLE(SceneManager)->RegisterScene(L"SampleScene", m_SampleScene);

		// 씬 로드하기
		GET_SINGLE(SceneManager)->LoadScene(L"SampleScene");
	}
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
