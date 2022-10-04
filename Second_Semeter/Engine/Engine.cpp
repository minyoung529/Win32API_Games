#include "pch.h"
#include "Engine.h"


void Engine::Init(const WindowInfo& window)
{
	m_window = window;
	ResizeWindow(window.width, window.height);

	// 그려질 화면의 크기 설정
	m_viewport = { 0, 0, static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	m_scissorRect = CD3DX12_RECT(0, 0, window.width, window.height);

	m_device = make_shared<Device>();
	m_cmdQueue = make_shared<CommandQueue>();
	m_swapChain = make_shared<SwapChain>();
	m_rootSignature = make_shared<RootSignature>();
	m_constantBuf = make_shared<ConstantBuffer>();

	m_input = make_shared<Input>();
	m_timer = make_shared<Timer>();

	m_device->Init();
	m_cmdQueue->Init(m_device->GetDevice(), m_swapChain);
	m_swapChain->Init(window, m_device->GetDevice(), m_device->GetDXGI(), m_cmdQueue->GetCmdQueue());
	m_rootSignature->Init(m_device->GetDevice());
	m_constantBuf->Init(sizeof(Transform), 256);

	m_input->Init(window.hwnd);
	m_timer->Init();
}

void Engine::Update()
{
	m_input->Update();
	m_timer->Update();

	ShowFps();
}

void Engine::Render()
{
	m_cmdQueue->RenderBegin(&m_viewport, &m_scissorRect);

	// 렌더링


	m_cmdQueue->RenderEnd();
}

void Engine::RenderBegin()
{
	m_cmdQueue->RenderBegin(&m_viewport, &m_scissorRect);
}

void Engine::RenderEnd()
{
	m_cmdQueue->RenderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	m_window.width = width;
	m_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_EX_OVERLAPPEDWINDOW, false);
	::SetWindowPos(m_window.hwnd, 0, 100, 100, width, height, 0);
}

void Engine::ShowFps()
{
	uint32 fps = m_timer->GetFps();

	WCHAR text[100] = TEXT("");
	::wsprintf(text, TEXT("FPS: %d"), fps);

	::SetWindowText(m_window.hwnd, text);
}
