#include "pch.h"
#include "Core.h"
#include "Object.h"

Core::Core():
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

    g_Obj.m_ptPos={m_ptResolution.x/2, m_ptResolution.y/2};
    g_Obj.m_ptScale={ 100,100 };

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

void Core::Update()
{
}

void Core::Render()
{
    Rectangle(m_hdc, 0, 0, 100, 100);
}
