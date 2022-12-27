#pragma once
class SwapChain
{
public:
	void Init(const WindowInfo& window, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void Present();
	void SwapIndex();

public:
	ComPtr<IDXGISwapChain> GetSwapChain() { return m_swapChain; }
	uint32 GetBackBufferIndex() { return m_backBufferIndex; }

private:
	void CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	
public:
	ComPtr<IDXGISwapChain>			m_swapChain;
	uint32	m_backBufferIndex = 0;
};

