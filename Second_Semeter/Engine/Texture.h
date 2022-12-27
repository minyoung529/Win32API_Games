#pragma once
#include "Object.h"

class Texture : public Object
{
public:
	Texture();
	virtual ~Texture();

public:
	virtual void Load(const wstring& path) override;

	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle() { return m_srvHeapBegin; }

public:
	float GetWidth() { return static_cast<float>(m_desc.Width); }
	float GetHeight() { return static_cast<float>(m_desc.Height); }

	ComPtr<ID3D12Resource> GetTex2D() { return m_tex2D; }
	ComPtr<ID3D12DescriptorHeap> GetSRV() { return m_srvHeap; }
	ComPtr<ID3D12DescriptorHeap> GetRTV() { return m_rtvHeap; }
	ComPtr<ID3D12DescriptorHeap> GetDSV() { return m_dsvHeap; }

public:
	void Create(DXGI_FORMAT format, uint32 width, uint32 height,
		const D3D12_HEAP_PROPERTIES& heapProperty, D3D12_HEAP_FLAGS heapFlags,
		D3D12_RESOURCE_FLAGS resFlags, Vec4 clearColor = Vec4());
	// 아예 처음부터 생성

	void CreateFromResource(ComPtr<ID3D12Resource> tex2D);
	// 기존 리소스 로드??

private:
	ScratchImage			 		m_image;
	ComPtr<ID3D12Resource>			m_tex2D;

	D3D12_RESOURCE_DESC				m_desc;

	// shader resource view
	ComPtr<ID3D12DescriptorHeap>	m_srvHeap;
	ComPtr<ID3D12DescriptorHeap>	m_rtvHeap; // swap chain
	ComPtr<ID3D12DescriptorHeap>	m_dsvHeap; // depth stencil

	D3D12_CPU_DESCRIPTOR_HANDLE		m_srvHeapBegin;
};