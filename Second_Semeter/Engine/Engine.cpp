#include "pch.h"
#include "Engine.h"

void Engine::Init(const WindowInfo& window)
{
	m_window = window;
	ResizeWindow(window.width, window.height);

	// 그려질 화면의 크기 설정
	viewport = { 0,0, static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	
	// 헬퍼 클래스
	scissorsRect = CD3DX12_RECT(0, 0, window.width, window.height);

	device = make_shared<Device>();
	commandQueue = make_shared<CommandQueue>();
	swapChain = make_shared<SwapChain>();
	rootSignature = make_shared<RootSignature>();
	constantBuffer = make_shared<ConstantBuffer>();
	input = make_shared<Input>();
	timer = make_shared<Timer>();

	device->Init();
	commandQueue->Init(device->GetDevice(), swapChain);
	swapChain->Init(window, device->GetDevice(), device->GetDXGI(), commandQueue->GetCmdQueue());
	
	rootSignature->Init(device->GetDevice());
	constantBuffer->Init(sizeof(Transform), 256);

	input->Init(window.hWnd);
	timer->Init();
}

void Engine::Update()
{
	input->Update();
	timer->Update();
	ShowFps();
}

void Engine::Render()
{
	commandQueue->RenderBegin(&viewport, &scissorsRect);

	// 렌더링

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
	::SetWindowPos(m_window.hWnd, 0, 100, 100, width, height, 0);
}

void Engine::ShowFps()
{
	uint32 fps = timer->GetFps();

	WCHAR text[100] = TEXT("");
	wsprintf(text, TEXT("FPS: %d"), fps);

	SetWindowText(m_window.hWnd, text);
}