#pragma once
#include "Device.h"
#include "SwapChain.h"
#include "CommandQueue.h"
#include "RootSignature.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"
#include "Texture.h"
#include "DepthStencileBuffer.h"

#include "Input.h"
#include "Timer.h"

class Engine
{
public:
	void Init(const WindowInfo& window);
	void Update();
	void Render();
	void RenderBegin();
	void RenderEnd();

public:
	void ResizeWindow(int32 width, int32 height);
	void ShowFps();
	void CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count);

public:
	shared_ptr<Device> GetDevice() { return m_device; }
	shared_ptr<SwapChain> GetSwapChain() { return m_swapChain; }
	shared_ptr<CommandQueue> GetCmdQueue() { return m_cmdQueue; }
	shared_ptr<RootSignature> GetRootSignature() { return m_rootSignature; }
	shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return m_tableDescHeap; }
	shared_ptr<DepthStencileBuffer> GetDepthStencileBuffer() { return m_depthStencileBuffer; }

	shared_ptr<Input> GetInput() { return m_input; }
	shared_ptr<Timer> GetTimer() { return m_timer; }

	shared_ptr<ConstantBuffer> GetConstantBuffer(CONSTANT_BUFFER_TYPE type) 
	{ 
		return m_constantBuffers[static_cast<uint8>(type)]; 
	}

private:
	WindowInfo		m_window;
	D3D12_VIEWPORT	m_viewport = {};
	D3D12_RECT		m_scissorRect = {};

private:
	shared_ptr<Device> m_device;
	shared_ptr<SwapChain> m_swapChain;
	shared_ptr<CommandQueue> m_cmdQueue;
	shared_ptr<RootSignature> m_rootSignature;
	shared_ptr<TableDescriptorHeap> m_tableDescHeap;
	shared_ptr<DepthStencileBuffer> m_depthStencileBuffer;

	shared_ptr<Input> m_input;
	shared_ptr<Timer> m_timer;

	vector<shared_ptr<ConstantBuffer>> m_constantBuffers;
};

