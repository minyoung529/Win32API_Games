#include "pch.h"
#include "Engine.h"

void Engine::Init(const WindowInfo& window)
{
	m_window = window;
	ResizeWindow(window.width, window.height);
}

void Engine::Render()
{
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	m_window.width = width;
	m_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_EX_OVERLAPPEDWINDOW, false);
	::SetWindowPos(m_window.hwnd, 0, 100, 100, width, height, 0);
}
