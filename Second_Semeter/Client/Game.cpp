#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"

void Game::Init(const WindowInfo& window)
{
	g_Engine->Init(window);

	m_gameObj = make_shared<GameObject>();
	m_gameObj->Init();
	
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

	m_gameObj->AddComponent(meshRenderer);
}

void Game::Update()
{
	g_Engine->Update();

	m_gameObj->Update();
	m_gameObj->LateUpdate();
}

void Game::Render()
{
	g_Engine->RenderBegin();

	m_gameObj->Render();

	g_Engine->RenderEnd();
}

void Game::Release()
{
}
