#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "Mesh.h"
#include "Shader.h"


void Game::Init(const WindowInfo& window)
{
	g_Engine->Init(window);

	m_mesh = make_shared<Mesh>();
	m_shader = make_shared<Shader>();

	vector<Vertex> vec(4);
	vec[0].pos = Vec3(-0.5f, 0.5f, 0.5f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[1].pos = Vec3(0.5f, 0.5f, 0.5f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[2].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	vec[3].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[3].color = Vec4(0.f, 1.f, 0.f, 1.f);

	vector<uint32> indexVec;
	{
		indexVec.push_back(0);
		indexVec.push_back(1);
		indexVec.push_back(2);

		indexVec.push_back(0);
		indexVec.push_back(2);
		indexVec.push_back(3);
	}

	m_mesh->Init(vec, indexVec);

	m_shader->Init(L"..\\Engine\\Default.hlsli");

	m_meshTrans.offset = {0.0f, 0.0f, 0.0};	
}

void Game::Update()
{
	g_Engine->Update();

	if (INPUT->GetButton(KEY_TYPE::W))
		m_meshTrans.offset.y += 1.0f * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::S))
		m_meshTrans.offset.y -= 1.0f * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::A))
		m_meshTrans.offset.x -= 1.0f * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::D))
		m_meshTrans.offset.x += 1.0f * DELTA_TIME;

	m_mesh->SetTransform(m_meshTrans);

	Color color;
	color.offset = { 1.0f, 0.0f, 0.0, 1.0f };
	m_mesh->SetColor(color);
}

void Game::Render()
{
	g_Engine->RenderBegin();

	m_shader->Render();
	m_mesh->Render();

	g_Engine->RenderEnd();
}

void Game::Release()
{
}
