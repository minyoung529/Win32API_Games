#include "pch.h"
#include "Game.h"
#include "Engine.h"

//typedef double (*DLL_ADD)(double a, double b);

void Game::Init(const WindowInfo& window)
{
	engine->Init(window);
	/*Arithmetic::Add(3.2f, 2.3f);

	std::string path = "..//Output//MyMath.dll";

	// �����ڵ� ������ �Լ� + A
	HMODULE hDll = ::LoadLibraryA(path.c_str());

	if (hDll)
	{
		// �Լ� ������
		DLL_ADD pFunc = (DLL_ADD)::GetProcAddress(hDll, "Add");
		int sum = pFunc(3.2f, 2.3f);
		sum += 1;
	}*/
}

void Game::Update()
{
}

void Game::Render()
{
	engine->Render();
}

void Game::Release()
{
}
