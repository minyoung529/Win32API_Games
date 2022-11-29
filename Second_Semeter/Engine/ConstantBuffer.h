#pragma once

enum class CONSTANT_BUFFER_TYPE : uint8
{
	GLOBAL,
	TRANSFORM,
	MATERIAL,
	END
};

enum
{
	CONSTANT_BUFFER_COUNT = static_cast<uint8>(CONSTANT_BUFFER_TYPE::END)
};

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

public:
	void Init(CBV_REGISTER reg, uint32 size, uint32 count);

	void Clear();
	void PushData(void* buffer, uint32 size);

	void PushGlobalData(void* buffer, uint32 size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(uint32 index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(uint32 index);

private:
	void CreateBuffer();
	void CreateView();

private:
	ComPtr<ID3D12Resource>		m_cbvBuffer;
	BYTE* m_mapedBuffer = nullptr;
	uint32 m_elementSize = 0;
	uint32 m_elementCount = 0;
	uint32 m_currentIndex = 0;

	ComPtr<ID3D12DescriptorHeap>	m_cbvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_cpuHandleBegin = {};
	uint32							m_handleIncrementSize = 0;

	CBV_REGISTER					m_reg = {};
};