#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "Mesh.h"
#include "Shader.h"

//typedef double (*DLL_ADD)(double a, double b);

void Game::Init(const WindowInfo& window)
{
	engine->Init(window);
	/*Arithmetic::Add(3.2f, 2.3f);

	std::string path = "..//Output//MyMath.dll";

	// 유니코드 문제로 함수 + A
	HMODULE hDll = ::LoadLibraryA(path.c_str());

	if (hDll)
	{
		// 함수 포인터
		DLL_ADD pFunc = (DLL_ADD)::GetProcAddress(hDll, "Add");
		int sum = pFunc(3.2f, 2.3f);
		sum += 1;
	}*/

	mesh = make_shared<Mesh>();
	shader = make_shared<Shader>();

	vector<Vertex> vec(3);

	vec[0].pos = Vec3(0.f, 0.5f, 0.5f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[1].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[1].color = Vec4(0.f, 1.0f, 0.f, 1.f);
	vec[2].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);

	mesh->Init(vec);
	shader->Init(L"..\\Engine\\Default.hlsli");

	meshTransform.offset = { 0.0f, 0.5f, 0.0f };
	color.color = { 1.f,0.f,0.f,1.0f };
}

void Game::Update()
{
	engine->Update();

	if (INPUT->GetButton(KEY_TYPE::W))
		meshTransform.offset.y += 1.f * DELTATIME;

	if (INPUT->GetButton(KEY_TYPE::A))
		meshTransform.offset.x -= 1.f * DELTATIME;

	if (INPUT->GetButton(KEY_TYPE::S))
		meshTransform.offset.y -= 1.f * DELTATIME;

	if (INPUT->GetButton(KEY_TYPE::D))
		meshTransform.offset.x += 1.f * DELTATIME;

	mesh->SetTransform(meshTransform);
	mesh->SetColor(color);
}

void Game::Render()
{
	engine->RenderBegin();

	shader->Render();
	mesh->Render();

	engine->RenderEnd();
}

void Game::Release()
{
}
