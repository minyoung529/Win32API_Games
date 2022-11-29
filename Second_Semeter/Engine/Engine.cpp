#include "pch.h"
#include "Engine.h"
#include "Material.h"
#include "SceneManager.h"
#include "Light.h"

void Engine::Init(const WindowInfo& window)
{
	m_window = window;
	
	// 그려질 화면의 크기 설정
	m_viewport = { 0, 0, static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	m_scissorRect = CD3DX12_RECT(0, 0, window.width, window.height);

	m_device = make_shared<Device>();
	m_cmdQueue = make_shared<CommandQueue>();
	m_swapChain = make_shared<SwapChain>();
	m_rootSignature = make_shared<RootSignature>();
	m_tableDescHeap = make_shared<TableDescriptorHeap>();
	m_depthStencileBuffer = make_shared<DepthStencileBuffer>();

	m_input = make_shared<Input>();
	m_timer = make_shared<Timer>();

	m_device->Init();
	m_cmdQueue->Init(m_device->GetDevice(), m_swapChain);
	m_swapChain->Init(window, m_device->GetDevice(), m_device->GetDXGI(), m_cmdQueue->GetCmdQueue());
	m_rootSignature->Init(m_device->GetDevice());
	m_tableDescHeap->Init(256);
	m_depthStencileBuffer->Init(window);

	m_input->Init(window.hwnd);
	m_timer->Init();

	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(LightParams), 1);
	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(TransformParams), 256);
	CreateConstantBuffer(CBV_REGISTER::b2, sizeof(MaterialParams), 256);

	ResizeWindow(window.width, window.height);
}

void Engine::Update()
{
	m_input->Update();
	m_timer->Update();

	GET_SINGLE(SceneManager)->Update();

	ShowFps();
}

void Engine::Render()
{
	m_cmdQueue->RenderBegin(&m_viewport, &m_scissorRect);

	// 렌더링
	GET_SINGLE(SceneManager)->Render();

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

	m_depthStencileBuffer->Init(m_window);
}

void Engine::ShowFps()
{
	uint32 fps = m_timer->GetFps();

	WCHAR text[100] = TEXT("");
	::wsprintf(text, TEXT("FPS: %d"), fps);

	::SetWindowText(m_window.hwnd, text);
}

void Engine::CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count)
{
	uint8 typeInt = static_cast<uint8>(reg);
	assert(m_constantBuffers.size() == typeInt);

	shared_ptr<ConstantBuffer> buffer = make_shared<ConstantBuffer>();
	buffer->Init(reg, bufferSize, count);
	m_constantBuffers.push_back(buffer);
}
