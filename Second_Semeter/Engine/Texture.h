#pragma once
#include "Object.h"

class Texture : public Object
{
public:
	Texture();
	virtual ~Texture();

public:
	virtual void Load(const wstring& path) override;

	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle() { return m_srvHandle; }

public:
	void CreateTexture(const wstring& path);
	void CreateView();

	float GetWidth() { return static_cast<float>(m_desc.Width); }
	float GetHeight() { return static_cast<float>(m_desc.Height); }

private:
	ScratchImage			 		m_image;
	ComPtr<ID3D12Resource>			m_tex2D;

	D3D12_RESOURCE_DESC				m_desc;

	ComPtr<ID3D12DescriptorHeap>	m_srvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_srvHandle;
};