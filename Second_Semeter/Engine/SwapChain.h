#pragma once
class SwapChain
{
	// ���� ����, �ĸ� ���� ����
public:
	// ����ü��, ����Ÿ�ٺ� ���� �� �ʿ���
	void Init(const WindowInfo& window, ComPtr<ID3D12Device> device,
		ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);

	void Present();
	void SwapIndex();

public:
	ComPtr<IDXGISwapChain> GetSwapChain() { return swapChain; }
	ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return rtvBuffer[index]; }

	ComPtr<ID3D12Resource> GetBackRTVBuffer() { return rtvBuffer[backBufferIndex]; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetBackRTV() { return rtvHandle[backBufferIndex]; }

private:
	void CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi,
		ComPtr<ID3D12CommandQueue> cmdQueue);
	void CreateRTV(ComPtr<ID3D12Device> device);

public:
	ComPtr<IDXGISwapChain>			swapChain;

	ComPtr<ID3D12Resource>			rtvBuffer[SWAP_CHAIN_BUFFER_COUNT];
	ComPtr<ID3D12DescriptorHeap>	rtvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		rtvHandle[SWAP_CHAIN_BUFFER_COUNT];

public:
	uint32	backBufferIndex = 0;
};