#pragma once
class SwapChain
{
public:
	void Init(const WindowInfo& window, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void Present();
	void SwapIndex();

public:
	ComPtr<IDXGISwapChain> GetSwapChain() { return m_swapChain; }
	ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return m_rtvBuffer[index]; }

	ComPtr<ID3D12Resource> GetBackRTVBuffer() { return m_rtvBuffer[m_backBufferIndex]; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetBackRTV() { return m_rtvHandle[m_backBufferIndex]; }

private:
	void CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void CreateRTV(ComPtr<ID3D12Device> device);
	
public:
	ComPtr<IDXGISwapChain>			m_swapChain;

	ComPtr<ID3D12Resource>			m_rtvBuffer[SWAP_CHAIN_BUFFER_COUNT];
	ComPtr<ID3D12DescriptorHeap>	m_rtvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_rtvHandle[SWAP_CHAIN_BUFFER_COUNT];

public:
	uint32	m_backBufferIndex = 0;
};

