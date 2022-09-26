#pragma once
#include "Device.h"
#include "SwapChain.h"
#include "CommandQueue.h"
#include "RootSignature.h"
#include "ConstantBuffer.h"
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
	
public:
	shared_ptr<Device> GetDevice() { return device; };
	shared_ptr<SwapChain> GetSwapChain() { return swapChain; };
	shared_ptr<CommandQueue> GetCmdQueue() { return commandQueue; };
	shared_ptr<RootSignature> GetRootSignature() { return rootSignature; };
	shared_ptr<ConstantBuffer> GetConstantBuffer() { return constantBuffer; };

	shared_ptr<Input> GetInput() { return input; }
	shared_ptr<Timer> GetTimer() { return timer; }

private:
	WindowInfo		m_window;
	D3D12_VIEWPORT	viewport = {};
	D3D12_RECT		scissorsRect = {};

private:
	shared_ptr<Device> device;
	shared_ptr<SwapChain> swapChain;
	shared_ptr<CommandQueue> commandQueue;
	shared_ptr<RootSignature> rootSignature;
	shared_ptr<ConstantBuffer> constantBuffer;

	shared_ptr<Input> input;
	shared_ptr<Timer> timer;
};