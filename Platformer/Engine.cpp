#include "Engine.h"

Engine* engine = NULL;

Engine::Engine() :
	prevCount{},
	curCount{},
	frequency{},
	deltaTime(0.0f),
	callCount(0),
	fps(0)
{
	engine = this;
	mSceneManager = new SceneManager;
	// 현재 카운트
	QueryPerformanceCounter(&prevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&frequency);
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
	QueryPerformanceCounter(&curCount);
	deltaTime = (float)(curCount.QuadPart - prevCount.QuadPart) /
		(float)(frequency.QuadPart);

	prevCount = curCount;

	++callCount;
	accumulate += deltaTime;

	if (accumulate > 1.0f)
	{
		fps = callCount;
		callCount = 0;
		accumulate = 0.0f;

		_RenderText(fps, deltaTime);
	}

	_Update(deltaTime);

	HDC hdc = GetDC(hWnd);
	_Render(hdc, deltaTime);
	ReleaseDC(hWnd, hdc);
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
	FillRect(hMemDC, &rect, (HBRUSH)GetStockObject(LTGRAY_BRUSH));

	if (mSceneManager)
		mSceneManager->Render(hMemDC, deltaTime);

	Render(hMemDC, deltaTime);

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
}

void Engine::_RenderText(UINT fps, float deltaTime)
{
	static TCHAR szTemp[256];
	swprintf_s(szTemp, TEXT("FPS : %d,  DT: %f"), fps, deltaTime);

	SetWindowTextW(hWnd, szTemp);
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
