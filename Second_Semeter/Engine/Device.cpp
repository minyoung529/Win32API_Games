#include "pch.h"
#include "Device.h"

void Device::Init()
{
	// D3D12 디버그층 활성화
#ifdef _DEBUG
	::D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
	debugController->EnableDebugLayer();
#endif // _DEBUG

	// 장치 생성
	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

	// DXGI 생성
	::CreateDXGIFactory(IID_PPV_ARGS(&dxgi));
}