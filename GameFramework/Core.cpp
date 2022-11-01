#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "TimeManager.h"
#include "KeyManager.h"

Core::Core() :
	m_ptResolution({}),
	m_hdc(0),
	m_memDC(0),
	m_hBit(0)
{
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hdc);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

Object g_Obj;

int Core::Init(HWND hWnd, POINT ptResolution)
{
	m_hWnd = hWnd;
	m_ptResolution = ptResolution;

	m_hdc = GetDC(hWnd);
	m_memDC = CreateCompatibleDC(m_hdc);
	m_hBit = CreateCompatibleBitmap(m_hdc, m_ptResolution.x, m_ptResolution.y);
	SelectObject(m_memDC, m_hBit);

	TimeManager::GetInst()->Init();
	KeyManager::GetInst()->Init();

	g_Obj.SetPos(Vector2(m_ptResolution.x / 2, m_ptResolution.y / 2));
	g_Obj.SetScale(Vector2(100, 100));

	// 해상도 맞게 조절
	RECT rt = { 0,0,ptResolution.x, ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 100, 100,
		rt.right - rt.left, rt.bottom - rt.top, 0);

	return S_OK;
}

void Core::Progress()
{
	TimeManager::GetInst()->Update();
	Update();
	Render();
}

void Core::Update()
{
	Vector2 pos = g_Obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		pos.x -= 100 * DT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		pos.x += 100 * DT;
	}

	g_Obj.SetPos(pos);
}

void Core::Render()
{
	//Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	PatBlt(m_memDC, 0, 0, m_ptResolution.x, m_ptResolution.y, BLACKNESS);

	Vector2 pos = g_Obj.GetPos();
	Vector2 scale = g_Obj.GetScale();

	Rectangle
	(
		m_memDC,
		(int)(pos.x - scale.x / 2.f),
		(int)(pos.y - scale.y / 2.f),
		(int)(pos.x + scale.x / 2.f),
		(int)(pos.y + scale.y / 2.f)
	);

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);
}
