#include "pch.h"
#include "Device.h"

void Device::Init()
{
	// D3D12 ������� Ȱ��ȭ
#ifdef _DEBUG
	::D3D12GetDebugInterface(IID_PPV_ARGS(&m_debugController));
	m_debugController->EnableDebugLayer();
#endif // _DEBUG

	// ��ġ ����
	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));

	// DXGI ����
	::CreateDXGIFactory(IID_PPV_ARGS(&m_dxgi));
}