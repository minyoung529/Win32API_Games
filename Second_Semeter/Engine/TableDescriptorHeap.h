#pragma once

class TableDescriptorHeap
{
public:
	void Init(uint32 count);
	void Clear();
	void SetCBV(D3D12_CPU_DESCRIPTOR_HANDLE srcHandle, CBV_REGISTER reg);
	void CommitTable();

public:
	ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() { return m_descHeap; }
	
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(uint32 reg);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(CBV_REGISTER reg);

private:
	ComPtr<ID3D12DescriptorHeap>	m_descHeap;
	uint32							m_handleSize = 0;
	uint32							m_groupSize = 0;
	uint32							m_groupCount = 0;

	uint32							m_currentGroupIndex = 0;


};