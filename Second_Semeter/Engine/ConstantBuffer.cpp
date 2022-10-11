#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
    if (m_cbvBuffer)
    {
        m_cbvBuffer->Unmap(0, nullptr);
        m_cbvBuffer = nullptr;
    }
}

void ConstantBuffer::Init(uint32 size, uint32 count)
{
    // 상수버프 : 256 바이트 배수로 만들어야 해..
    m_elementSize = (size + 255) & ~255;
    m_elementCount = count;

    CreateBuffer();
    CreateView();
}

void ConstantBuffer::Clear()
{
    m_currentIndex = 0;
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::PushData(int32 rootParamIndex, void* buffer, uint32 size)
{
    assert(m_currentIndex < m_elementCount);

    ::memcpy(&m_mapedBuffer[m_currentIndex * m_elementSize], buffer, size);

    D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = GetCpuHandle(m_currentIndex);

    m_currentIndex++;

    return cpuHandle;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGpuVirtualAddress(uint32 index)
{
    D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = m_cbvBuffer->GetGPUVirtualAddress();
    objCBAddress += index * m_elementSize;
    return objCBAddress;
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::GetCpuHandle(uint32 index)
{
    return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_cpuHandleBegin, index * m_handleIncrementSize);
}

void ConstantBuffer::CreateBuffer()
{
    uint32 bufferSize = m_elementSize * m_elementCount;
    D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

    DEVICE->CreateCommittedResource(
        &heapProperty,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_cbvBuffer));

    m_cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_mapedBuffer));
}

void ConstantBuffer::CreateView()
{
    D3D12_DESCRIPTOR_HEAP_DESC cbvDesc = {};
    cbvDesc.NumDescriptors = m_elementCount;
    cbvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    cbvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    DEVICE->CreateDescriptorHeap(&cbvDesc, IID_PPV_ARGS(&m_cbvHeap));

    m_cpuHandleBegin = m_cbvHeap->GetCPUDescriptorHandleForHeapStart();
    m_handleIncrementSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    for (uint32 i = 0; i < m_elementCount; ++i)
    {
        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
        cbvDesc.BufferLocation = m_cbvBuffer->GetGPUVirtualAddress() + static_cast<uint64>(m_elementSize) * i;
        cbvDesc.SizeInBytes = m_elementSize;

        D3D12_CPU_DESCRIPTOR_HANDLE cbvHandle = GetCpuHandle(i);

        DEVICE->CreateConstantBufferView(&cbvDesc, cbvHandle);
    }

}
