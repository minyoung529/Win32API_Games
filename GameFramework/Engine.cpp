#include "Engine.h"

Engine::Engine() : interval(30.0f)
{
	lastTime = currentTime = (float)timeGetTime();
	mSceneManager = new SceneManager;
}

Engine::~Engine()
{
	if (mSceneManager)
		delete mSceneManager;
}

// 장치의 초기화, 메세지 루프 들어가기 전
void Engine::StartUp()
{
	Input.Init();
	Sound.Init();

	if (mSceneManager)
		mSceneManager->Init();

	Init();
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
		_Render(hdc, frameDelta);
		ReleaseDC(hWnd, hdc);

		_RenderText(frameDelta);
		lastTime = currentTime;
	}
}

//장치의 종료
void Engine::Cleanup()
{
	Input.Release();
	Sound.Release();

	if (mSceneManager)
		mSceneManager->Release();
	Release();
}

void Engine::_Update(float deltaTime)
{
	Input.Update();

	if (mSceneManager)
		mSceneManager->Update(deltaTime);

	Update(deltaTime);
}

void Engine::_Render(HDC hdc, float deltaTime)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	FillRect(hMemDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	if (mSceneManager)
		mSceneManager->Render(hdc, deltaTime);

	Render(hMemDC, deltaTime);

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
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
