#pragma once

class Texture
{
public:
	void Init(const wstring& path);

	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle() { return m_srvHandle; }

public:
	void CreateTexture(const wstring& path);
	void CreateView();

private:
	ScratchImage			 		m_image;
	ComPtr<ID3D12Resource>			m_tex2D;

	ComPtr<ID3D12DescriptorHeap>	m_srvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_srvHandle;
};