#include "pch.h"
#include "Engine.h"

void Engine::Init(const WindowInfo& window)
{
	m_window = window;
	ResizeWindow(window.width, window.height);

	// �׷��� ȭ���� ũ�� ����
	viewport = { 0,0, static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	
	// ���� Ŭ����
	scissorsRect = CD3DX12_RECT(0, 0, window.width, window.height);

	device = make_shared<Device>();
	commandQueue = make_shared<CommandQueue>();
	swapChain = make_shared<SwapChain>();
	rootSignature = make_shared<RootSignature>();

	device->Init();
	commandQueue->Init(device->GetDevice(), swapChain);
	swapChain->Init(window, device->GetDevice(), device->GetDXGI(), commandQueue->GetCmdQueue());
	rootSignature->Init(device->GetDevice());
}

void Engine::Render()
{
	commandQueue->RenderBegin(&viewport, &scissorsRect);

	// ������

	commandQueue->RenderEnd();
}

void Engine::RenderBegin()
{
	commandQueue->RenderBegin(&viewport, &scissorsRect);
}

void Engine::RenderEnd()
{
	commandQueue->RenderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	m_window.width = width;
	m_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_EX_OVERLAPPEDWINDOW, false);
	::SetWindowPos(m_window.hwnd, 0, 100, 100, width, height, 0);

}
