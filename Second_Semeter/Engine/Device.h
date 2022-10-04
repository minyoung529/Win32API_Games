#pragma once

class Device
{
public:
	void Init();
	ComPtr<IDXGIFactory> GetDXGI() { return m_dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return m_device; }

private:
	// COMPtr
	ComPtr<ID3D12Debug>		m_debugController;
	ComPtr<IDXGIFactory>	m_dxgi;		// 화면 관련 기능들
	ComPtr<ID3D12Device>	m_device;	// 각종 객체 생성
};

