#pragma once
#include "Device.h"
#include "SwapChain.h"
#include "CommandQueue.h"
#include "RootSignature.h"

class Engine
{
public:
	void Init(const WindowInfo& window);
	void Render();
	void RenderBegin();
	void RenderEnd();

public:
	void ResizeWindow(int32 width, int32 height);
	
public:
	shared_ptr<Device> GetDevice() { return device; };
	shared_ptr<SwapChain> GetSwapChain() { return swapChain; };
	shared_ptr<CommandQueue> GetCmdQueue() { return commandQueue; };
	shared_ptr<RootSignature> GetRootSignature() { return rootSignature; };

private:
	WindowInfo		m_window;
	D3D12_VIEWPORT	viewport = {};
	D3D12_RECT		scissorsRect = {};

private:
	shared_ptr<Device> device;
	shared_ptr<SwapChain> swapChain;
	shared_ptr<CommandQueue> commandQueue;
	shared_ptr<RootSignature> rootSignature;
};