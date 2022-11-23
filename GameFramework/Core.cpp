#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"

Core::Core() :
	m_ptResolution({}),
	m_hdc(0),
	m_memDC(0),
	m_hBit(0),
	m_arrBrush{},
	m_arrPen{}
{
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hdc);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int Core::Init(HWND hWnd, POINT ptResolution)
{
	m_hWnd = hWnd;
	m_ptResolution = ptResolution;

	m_hdc = GetDC(hWnd);
	m_memDC = CreateCompatibleDC(m_hdc);
	m_hBit = CreateCompatibleBitmap(m_hdc, m_ptResolution.x, m_ptResolution.y);
	SelectObject(m_memDC, m_hBit);

	CreateBrushPen();

	// ===== Manager 초기화 ======
	TimeManager::GetInst()->Init();
	KeyManager::GetInst()->Init();
	PathManager::GetInst()->Init();
	SceneManager::GetInst()->Init();
	// ===== Manager 초기화 ======

	// 해상도 맞게 조절
	RECT rt = { 0,0,ptResolution.x, ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 100, 100,
		rt.right - rt.left, rt.bottom - rt.top, 0);

	return S_OK;
}

void Core::Progress()
{
	Update();
	Render();
}

void Core::CreateBrushPen()
{
}

void Core::Update()
{
	TimeManager::GetInst()->Update();
	KeyManager::GetInst()->Update();
	SceneManager::GetInst()->Update();
}

void Core::Render()
{
	PatBlt(m_memDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS);
	
	SceneManager::GetInst()->Render(m_memDC);

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	// 제목에 dt 띄우는 함수
	// TimeManager::GetInst()->Render();
}
