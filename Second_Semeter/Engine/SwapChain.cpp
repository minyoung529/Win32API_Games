#include "pch.h"
#include "SwapChain.h"

void SwapChain::Init(const WindowInfo& window, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	CreateSwapChain(window, dxgi, cmdQueue);
	CreateRTV(device);
}

void SwapChain::Present()
{
	swapChain->Present(0, 0);
}

void SwapChain::SwapIndex()
{
	// �� ���� ���ư��� 
	backBufferIndex = (backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}

void SwapChain::CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	// ������ ���� ���� ����
	swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;

	// �ĸ� ����, ���� ���ۿ� ���� ����
	sd.BufferDesc.Width = static_cast<uint32>(window.width);	// ������ �ػ� �ʺ�
	sd.BufferDesc.Height = static_cast<uint32>(window.height);	// ������ �ػ� ����
	sd.BufferDesc.RefreshRate.Numerator = 60;					// ȭ�� ���� ���� (������)
	sd.BufferDesc.RefreshRate.Denominator = 1;					// ȭ�� ���� ����
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// ������ ���÷��� ����
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Count = 1;							// ��Ƽ ���ø� OFF
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// �ĸ� ���ۿ� �������� ��
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT;			// ����+�ĸ� ����
	sd.OutputWindow = window.hwnd;
	sd.Windowed = window.windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		// �����ĸ���� ��ü�� ���������� ��������
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// ���� ü���� �����
	dxgi->CreateSwapChain(cmdQueue.Get(), &sd, &swapChain);

	for (int32 i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		// ���� Ÿ�� ������ ���� ä����
		// ó������ ���� �����.
		swapChain->GetBuffer(i, IID_PPV_ARGS(&rtvBuffer[i]));
	}
}

void SwapChain::CreateRTV(ComPtr<ID3D12Device> device)
{
	// Descriptor (DX12) = View (~DX11)
	// [������ ��]���� RTV ����
	// DX11�� RTV(RenderTargetView), DSV(DepthStencilView),
	// CBV(ConstantBufferView), SRV(ShaderResourceView), UAV(UnorderedAccessView)�� ����

	// ���۸� �������� ���� �����
	int32 rtvHeapSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_DESCRIPTOR_HEAP_DESC rtvDesc;
	rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvDesc.NodeMask = 0;

	// ���� ������ �����ͳ��� �迭�� ����
	// RTV ��� : [ ] [ ]
	device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&rtvHeap));
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapBegin = rtvHeap->GetCPUDescriptorHandleForHeapStart();

	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		// ���ҽ��� �����ϱ� ���� �� �ڵ� => ��
		// descriptor => �޸��� ����
		rtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeapBegin, i * rtvHeapSize);
		device->CreateRenderTargetView(rtvBuffer[i].Get(), nullptr, rtvHandle[i]);
	}
}

// ���� => ��(descriptor) => ��