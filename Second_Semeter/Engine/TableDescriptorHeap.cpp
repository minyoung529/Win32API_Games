#include "pch.h"
#include "TableDescriptorHeap.h"
#include "engine.h"

void TableDescriptorHeap::Init(uint32 count)
{
	m_groupCount = count;

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = count * REGISTER_COUNT;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	DEVICE->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_descHeap));

	m_handleSize = DEVICE->GetDescriptorHandleIncrementSize(desc.Type);
	m_groupSize = m_handleSize * REGISTER_COUNT;
}

void TableDescriptorHeap::Clear()
{
	m_currentGroupIndex = 0;
}

void TableDescriptorHeap::SetCBV(D3D12_CPU_DESCRIPTOR_HANDLE srcHandle, CBV_REGISTER reg)
{
	D3D12_CPU_DESCRIPTOR_HANDLE destHandle = GetCpuHandle(reg);

	// 사용하는 descriptor가 하나임
	uint32 destRange = 1;
	uint32 srcRange = 1;

	// cpu desc handle > my desc handle(gpu, shader) 복사
	DEVICE->CopyDescriptors(1, &destHandle, &destRange, 1, &srcHandle, &srcRange, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void TableDescriptorHeap::CommitTable()
{
	D3D12_GPU_DESCRIPTOR_HANDLE handle = m_descHeap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += m_currentGroupIndex * m_groupSize;
	CMD_LIST->SetGraphicsRootDescriptorTable(0, handle);

	m_currentGroupIndex++;
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptorHeap::GetCpuHandle(uint32 reg)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handle = m_descHeap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += m_currentGroupIndex * m_groupSize;
	handle.ptr += reg * m_handleSize;

	return handle;
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptorHeap::GetCpuHandle(CBV_REGISTER reg)
{
	return GetCpuHandle(static_cast<uint32>(reg));
}
