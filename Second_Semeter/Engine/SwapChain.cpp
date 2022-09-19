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
	// 백 버퍼 돌아가기 
	backBufferIndex = (backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}

void SwapChain::CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	// 이전에 만든 정보 리셋
	swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;

	// 후면 버퍼, 전면 버퍼에 관한 설정
	sd.BufferDesc.Width = static_cast<uint32>(window.width);	// 버퍼의 해상도 너비
	sd.BufferDesc.Height = static_cast<uint32>(window.height);	// 버퍼의 해상도 높이
	sd.BufferDesc.RefreshRate.Numerator = 60;					// 화면 갱신 비율 (프레임)
	sd.BufferDesc.RefreshRate.Denominator = 1;					// 화면 갱신 비율
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// 버퍼의 디스플레이 형식
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Count = 1;							// 멀티 샘플링 OFF
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// 후면 버퍼에 렌더링할 것
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT;			// 전면+후면 버퍼
	sd.OutputWindow = window.hwnd;
	sd.Windowed = window.windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		// 전면후면버퍼 교체시 이전프레임 정보버림
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// 스왑 체인을 만든다
	dxgi->CreateSwapChain(cmdQueue.Get(), &sd, &swapChain);

	for (int32 i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		// 렌더 타겟 버퍼의 값이 채워짐
		// 처음으로 버퍼 만든다.
		swapChain->GetBuffer(i, IID_PPV_ARGS(&rtvBuffer[i]));
	}
}

void SwapChain::CreateRTV(ComPtr<ID3D12Device> device)
{
	// Descriptor (DX12) = View (~DX11)
	// [서술자 힙]으로 RTV 생성
	// DX11의 RTV(RenderTargetView), DSV(DepthStencilView),
	// CBV(ConstantBufferView), SRV(ShaderResourceView), UAV(UnorderedAccessView)를 전부

	// 버퍼를 기준으로 힙을 만든다
	int32 rtvHeapSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_DESCRIPTOR_HEAP_DESC rtvDesc;
	rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvDesc.NodeMask = 0;

	// 같은 종류의 데이터끼리 배열로 관리
	// RTV 목록 : [ ] [ ]
	device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&rtvHeap));
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapBegin = rtvHeap->GetCPUDescriptorHandleForHeapStart();

	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		// 리소스에 접근하기 위한 게 핸들 => 뷰
		// descriptor => 메모리의 정보
		rtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeapBegin, i * rtvHeapSize);
		device->CreateRenderTargetView(rtvBuffer[i].Get(), nullptr, rtvHandle[i]);
	}
}

// 버퍼 => 힙(descriptor) => 뷰