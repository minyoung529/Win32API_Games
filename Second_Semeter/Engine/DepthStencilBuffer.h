#pragma once
class DepthStencilBuffer
{
public:
	void Init(const WindowInfo& window, DXGI_FORMAT dsvFormat = DXGI_FORMAT_D32_FLOAT);

	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCpuHandle() { return m_dsvHandle; }
	DXGI_FORMAT GetDSVFormat() { return m_dsvFormat; }

private:
	ComPtr<ID3D12Resource>			m_dsvBuffer;
	ComPtr<ID3D12DescriptorHeap>	m_dsvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_dsvHandle = {};
	DXGI_FORMAT						m_dsvFormat;
};