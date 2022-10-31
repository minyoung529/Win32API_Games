#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "TimeManager.h"
#include "KeyManager.h"

Core::Core() :
	m_ptResolution({}),
	m_hdc(0)
{
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hdc);
}

Object g_Obj;

int Core::Init(HWND hWnd, POINT ptResolution)
{
	m_hWnd = hWnd;
	m_ptResolution = ptResolution;

	m_hdc = GetDC(hWnd);

	TimeManager::GetInst()->Init();
	KeyManager::GetInst()->Init();

	g_Obj.SetPos(Vector2( m_ptResolution.x / 2, m_ptResolution.y / 2 ));
	g_Obj.SetScale(Vector2( 100,100 ));

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
	Rectangle(m_hdc, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	Vector2 pos = g_Obj.GetPos();
	Vector2 scale = g_Obj.GetScale();

	Rectangle
	(
		m_hdc,
		(int)(pos.x - scale.x / 2.f),
		(int)(pos.y - scale.y / 2.f),
		(int)(pos.x + scale.x / 2.f),
		(int)(pos.y + scale.y / 2.f)
	);
}
