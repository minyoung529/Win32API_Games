#include "Engine.h"

Engine::Engine() : interval(30.0f)
{
	lastTime = currentTime = (float)timeGetTime();
}

Engine::~Engine()
{
}

// 장치의 초기화, 메세지 루프 들어가기 전
void Engine::StartUp()
{
}

// 게임 루프
void Engine::MainLoop()
{
	currentTime = (float)timeGetTime();
	float frameDelta = (currentTime - lastTime) * 0.001f;

	if (frameDelta >= 1.0f / interval)
	{
		_Update(frameDelta);
		HDC hdc = GetDC(hWnd);
		Render(hdc, frameDelta);
		ReleaseDC(hWnd, hdc);

		_RenderText(frameDelta);
		lastTime = currentTime;
	}
}

//장치의 종료
void Engine::Cleanup()
{
	Release();
	Init();
}

void Engine::_Update(float deltaTime)
{
	Update(deltaTime);
}

void Engine::_Render(HDC hdc, float deltaTime)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, bitmap);
	FillRect(hMemDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	Render(hMemDC, deltaTime);
	BitBlt(hdc, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(bitmap);
	DeleteDC(hMemDC);
}

void Engine::_RenderText(float deltaTime)
{
	static DWORD frameCount; // 프레임 카운트
	static float timeElapsed = 0.0f; // 흐른 시간

	timeElapsed += deltaTime;
	frameCount++;

	if (timeElapsed >= 1.0f)
	{
		static TCHAR szTemp[256];
		wsprintf(szTemp, TEXT("게임 속도 FPS : %d"), frameCount);
		SetWindowTextW(hWnd, szTemp);

		frameCount = 0;
		timeElapsed = 0.01f;
	}
}

void Engine::Init()
{
}

void Engine::Update(float deltaTime)
{
}

void Engine::Render(HDC hdc, float deltaTime)
{
}

void Engine::Release()
{
}
