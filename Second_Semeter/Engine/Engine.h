#pragma once

class Engine
{
public:
	void Init(const WindowInfo& window);
	void Render();

public:
	void ResizeWindow(int32 width, int32 height);

private:
	WindowInfo		m_window;
	D3D12_VIEWPORT	viewport = {};
	D3D12_RECT		scissorsRect = {};

private:
	shared_ptr<class Device> device;
	shared_ptr<class SwapChain> swapChain;
	shared_ptr<class CommandQueue> commandQueue;
};