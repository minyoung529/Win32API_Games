#include "pch.h"
#include "ConstantBuffer.h"
#include "engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	if (cbvBuffer)
	{
		cbvBuffer->Unmap(0, nullptr);
		cbvBuffer = nullptr;
	}
}

void ConstantBuffer::Init(uint32 size, uint32 count)
{
	// ��� ����: 256����Ʈ ����� ������ �Ѵ�

	// ��� ������ ������ + 255, ���� and ����
	elementSize = (size + 255) & ~255;
	elementCount = count;
	CreateBuffer();
}

void ConstantBuffer::Clear()
{
	currentIndex = 0;
}

void ConstantBuffer::PushData(int32 rootParamIndex, void* buffer, uint32 size)
{
	assert(currentIndex < elementCount);

	// ���� �迭�� ���� => currentIndex * elementSize
	::memcpy(&mapedBuffer[currentIndex * elementSize], buffer, size);

	D3D12_GPU_VIRTUAL_ADDRESS address = GetGPUVirtualAddress(currentIndex);
	
	CMD_LIST->SetGraphicsRootConstantBufferView(rootParamIndex, address);

	currentIndex++;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGPUVirtualAddress(uint32 index)
{
	// ����޸�
	D3D12_GPU_VIRTUAL_ADDRESS objCBAdress = cbvBuffer->GetGPUVirtualAddress();
	objCBAdress += index * elementSize;
	return objCBAdress;
}

void ConstantBuffer::CreateBuffer()
{
	// ���۸� �����
	uint32 bufferSize = elementSize * elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&cbvBuffer));

	// ������ void ������
	// cvb ���ۿ� maped ���۸� �����߰�, ������ �� ������ maped ���ۿ��� �����͸� ä���
	// cvb ���۰� ������ �ִ´�??
	cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mapedBuffer));
}